FROM mirror.gcr.io/prom/alertmanager:v0.27.0 AS binary

FROM mirror.gcr.io/library/debian:bookworm-slim
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y gettext-base tini ca-certificates \
    && rm -rf /var/lib/apt/lists/*

COPY --from=binary /bin/alertmanager /bin/alertmanager
COPY entrypoint.sh /entrypoint.sh

RUN mkdir -p /alertmanager /etc/alertmanager \
    && chown -R nobody:nogroup /alertmanager /etc/alertmanager \
    && chmod +x /entrypoint.sh

USER nobody

EXPOSE 9093

ENTRYPOINT ["/usr/bin/tini", "--", "/entrypoint.sh"]
