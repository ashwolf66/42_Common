FROM mirror.gcr.io/library/debian:bookworm-slim
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
	&& apt-get install -y prometheus gettext-base tini \
	&& rm -rf /var/lib/apt/lists/*

COPY conf/prometheus.yml /etc/prometheus/prometheus.yml
COPY conf/alerts.yml.template /etc/prometheus/alerts.yml.template
COPY entrypoint.sh /entrypoint.sh

RUN mkdir -p /prometheus \
	&& chown -R prometheus:prometheus /prometheus /etc/prometheus \
	&& chmod +x /entrypoint.sh

USER prometheus

EXPOSE 9090

ENTRYPOINT ["/usr/bin/tini", "--", "/entrypoint.sh"]
CMD ["/usr/bin/prometheus", "--config.file=/etc/prometheus/prometheus.yml", "--storage.tsdb.path=/prometheus", "--web.console.libraries=/usr/share/prometheus/console_libraries", "--web.console.templates=/usr/share/prometheus/consoles"]
