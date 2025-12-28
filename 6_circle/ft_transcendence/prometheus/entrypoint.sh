#!/bin/sh

# Default values if not set
export ALERT_TIME=${ALERT_TIME:-300}
export CPU_PERCENTAGE=${CPU_PERCENTAGE:-80}
export MEM_PERCENTAGE=${MEM_PERCENTAGE:-85}

# Substitute environment variables in alerts.yml.template and write to alerts.yml
envsubst '${ALERT_TIME} ${CPU_PERCENTAGE} ${MEM_PERCENTAGE}' < /etc/prometheus/alerts.yml.template > /etc/prometheus/alerts.yml

# Execute the passed command (Prometheus)
exec "$@"
