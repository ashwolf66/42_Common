#!/bin/sh
set -eu

KIBANA_URL=${KIBANA_URL:-https://kibana:5601}
ELASTICSEARCH_URL=${ELASTICSEARCH_URL:-https://elasticsearch:9200}
DATA_VIEW_ID=${DATA_VIEW_ID:-ft-transcendence-logs}
DATA_VIEW_TITLE=${DATA_VIEW_TITLE:-ft-transcendence-*}
DATA_VIEW_NAME=${DATA_VIEW_NAME:-FT Transcendence Logs}
TIME_FIELD=${TIME_FIELD:-@timestamp}
SEARCH_ID=${SEARCH_ID:-ft-log-overview-search}
SEARCH_TITLE=${SEARCH_TITLE:-Log Overview}
DASHBOARD_ID=${DASHBOARD_ID:-ft-logs-dashboard}
DASHBOARD_TITLE=${DASHBOARD_TITLE:-FT Logs Dashboard}

if [ -n "${KIBANA_USER:-}" ] && [ -n "${KIBANA_PASS:-}" ]; then
  CURL_AUTH="-u ${KIBANA_USER}:${KIBANA_PASS}"
else
  CURL_AUTH=""
fi

ES_SUPERUSER=${ELASTIC_USER:-elastic}
ES_SUPERPASS=${ELASTIC_PASSWORD:-changeme}

curl_base() {
  # shellcheck disable=SC2086
  curl -s -k -f ${CURL_AUTH} "$@"
}

echo "Waiting for Elasticsearch to be ready..."
until curl_base "${ELASTICSEARCH_URL}/_cluster/health?wait_for_status=yellow&timeout=50s" > /dev/null 2>&1; do
    echo "Elasticsearch is not ready yet. Retrying in 5 seconds..."
    sleep 5
done
echo "Elasticsearch is ready."

echo "Setting kibana_system password..."
curl -s -k -f -u "${ES_SUPERUSER}:${ES_SUPERPASS}" -X POST "${ELASTICSEARCH_URL}/_security/user/kibana_system/_password" \
  -H "Content-Type: application/json" \
  -d "{\"password\":\"${KIBANA_SYSTEM_PASSWORD:-${ES_SUPERPASS}}\"}" >/dev/null && echo "kibana_system password set." || echo "kibana_system password set (best-effort)."

echo "Waiting for Kibana to be ready..."
until curl_base "${KIBANA_URL}/api/status" > /dev/null 2>&1; do
    echo "Kibana is not ready yet. Retrying in 5 seconds..."
    sleep 5
done
echo "Kibana is ready."

echo "Waiting 10s for Kibana plugins to initialize..."
sleep 10

echo "Creating Elasticsearch Index Template..."
curl_base -X PUT "${ELASTICSEARCH_URL}/_index_template/ft_transcendence_template" \
  -H "Content-Type: application/json" \
  -d '{
    "index_patterns": ["ft-transcendence-*"],
    "template": {
      "mappings": {
        "properties": {
          "@timestamp": { "type": "date" },
          "message": { "type": "text" },
          "log_value": { "type": "text" },
          "tag": { "type": "keyword" }
        }
      }
    },
    "priority": 100
  }'
echo "Index Template created."

echo "Ensuring at least one index exists (seed if empty)..."
SEED_INDEX=${SEED_INDEX:-ft-transcendence-seed}
EXISTING=$(curl -s -k "${ELASTICSEARCH_URL}/_cat/indices/ft-transcendence-*?h=index")
if [ -z "${EXISTING}" ]; then
  NOW_ISO=$(date -u '+%Y-%m-%dT%H:%M:%SZ')
  curl_base -X PUT "${ELASTICSEARCH_URL}/${SEED_INDEX}" \
    -H "Content-Type: application/json" \
    -d '{"mappings":{"properties":{"@timestamp":{"type":"date"},"log_value":{"type":"text"},"message":{"type":"text"},"tag":{"type":"keyword"}}}}'
  curl_base -X POST "${ELASTICSEARCH_URL}/${SEED_INDEX}/_doc" \
    -H "Content-Type: application/json" \
    -d "{\"@timestamp\":\"${NOW_ISO}\",\"log_value\":\"seed event\",\"message\":\"seed event\",\"tag\":\"seed\"}"
  echo "Seed index ${SEED_INDEX} created with one document."
else
  echo "Index already exists; skipping seed creation."
fi

echo "Creating/Updating Data View..."
curl_base -X POST "${KIBANA_URL}/api/saved_objects/index-pattern/${DATA_VIEW_ID}?overwrite=true" \
  -H "kbn-xsrf: true" \
  -H "Content-Type: application/json" \
  -d "{
    \"attributes\": {
       \"title\": \"${DATA_VIEW_TITLE}\",
       \"name\": \"${DATA_VIEW_NAME}\",
       \"timeFieldName\": \"${TIME_FIELD}\"
    }
  }"
echo "Data View ensured."

echo "Setting Default Data View..."
curl_base -X POST "${KIBANA_URL}/api/kibana/settings" \
  -H "kbn-xsrf: true" \
  -H "Content-Type: application/json" \
  -d "{\"changes\":{\"defaultIndex\":\"${DATA_VIEW_ID}\"}}"
echo "Default Data View set."

echo "Waiting for indices to exist before refreshing fields..."
for i in $(seq 1 30); do
  EXISTING=$(curl -s -k "${ELASTICSEARCH_URL}/_cat/indices/ft-transcendence-*?h=index")
  if [ -n "${EXISTING}" ]; then
    echo "Index detected, refreshing data view fields..."
    curl -s -k ${CURL_AUTH} -X POST "${KIBANA_URL}/api/data_views/data_view/${DATA_VIEW_ID}/refresh_fields" \
      -H "kbn-xsrf: true" >/dev/null 2>&1 || true
    echo "Fields refresh attempted."
    break
  fi
  echo "No index yet. Retry ${i}/30 in 2s..."
  sleep 2
done

echo "Creating Saved Search (${SEARCH_TITLE})..."
SEARCH_PAYLOAD=$(cat <<EOF
{
  "attributes": {
    "title": "${SEARCH_TITLE}",
    "description": "Default view with timestamp, service, tag, and message",
    "columns": ["@timestamp", "service", "tag", "message"],
    "sort": [["@timestamp", "desc"]],
    "kibanaSavedObjectMeta": {
      "searchSourceJSON": "{\"index\":\"${DATA_VIEW_ID}\",\"query\":{\"query\":\"\",\"language\":\"kuery\"},\"filter\":[]}"
    }
  },
  "references": [
    {"name":"kibanaSavedObjectMeta.searchSourceJSON.index","type":"index-pattern","id":"${DATA_VIEW_ID}"}
  ]
}
EOF
)

if ! curl_base -X POST "${KIBANA_URL}/api/saved_objects/search/${SEARCH_ID}?overwrite=true" \
  -H "kbn-xsrf: true" \
  -H "Content-Type: application/json" \
  --data-raw "${SEARCH_PAYLOAD}"; then
  echo "Saved Search creation failed" >&2
  exit 1
fi
echo "Saved Search ensured."

echo "Creating Dashboard (${DASHBOARD_TITLE})..."
PANELS_JSON='[{"panelIndex":"1","gridData":{"x":0,"y":0,"w":24,"h":15,"i":"1"},"version":"8.12.0","type":"search","panelRefName":"panel_0","embeddableConfig":{}}]'
PANELS_JSON_ESCAPED=$(printf '%s' "${PANELS_JSON}" | sed 's/"/\\"/g')

DASHBOARD_PAYLOAD=$(cat <<EOF
{
  "attributes": {
    "title": "${DASHBOARD_TITLE}",
    "description": "Auto-generated overview dashboard for ft_transcendence logs",
    "panelsJSON": "${PANELS_JSON_ESCAPED}",
    "version": 1,
    "timeRestore": false,
    "optionsJSON": "{\"useMargins\":true,\"syncColors\":false,\"syncTooltips\":false,\"hidePanelTitles\":false}",
    "kibanaSavedObjectMeta": {
      "searchSourceJSON": "{\"query\":{\"language\":\"kuery\",\"query\":\"\"},\"filter\":[]}"
    }
  },
  "references": [
    {"name":"panel_0","type":"search","id":"${SEARCH_ID}"}
  ]
}
EOF
)

for i in $(seq 1 5); do
  HTTP_CODE=$(curl -s -k ${CURL_AUTH} -o /tmp/kbn_dashboard_resp.json -w "%{http_code}" \
    -X POST "${KIBANA_URL}/api/saved_objects/dashboard/${DASHBOARD_ID}?overwrite=true" \
    -H "kbn-xsrf: true" \
    -H "Content-Type: application/json" \
    --data-raw "${DASHBOARD_PAYLOAD}" || true)

  if [ "${HTTP_CODE}" = "200" ] || [ "${HTTP_CODE}" = "201" ]; then
    echo "Dashboard ensured."
    break
  fi

  echo "Dashboard creation failed (attempt ${i}/5, status ${HTTP_CODE}). Response: $(cat /tmp/kbn_dashboard_resp.json 2>/dev/null)" >&2
  sleep 5
done

if ! ( [ "${HTTP_CODE}" = "200" ] || [ "${HTTP_CODE}" = "201" ] ); then
  echo "Dashboard creation failed after retries" >&2
  exit 1
fi

echo "Kibana bootstrap complete. Dashboard available at ${KIBANA_URL}/app/dashboards#/view/${DASHBOARD_ID}"
