FROM mirror.gcr.io/library/debian:bookworm-slim
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
	&& apt-get install -y wget gnupg ca-certificates \
	&& mkdir -p /etc/apt/keyrings \
	&& wget -qO- https://apt.grafana.com/gpg.key | gpg --dearmor -o /etc/apt/keyrings/grafana.gpg \
	&& echo "deb [signed-by=/etc/apt/keyrings/grafana.gpg] https://apt.grafana.com stable main" > /etc/apt/sources.list.d/grafana.list \
	&& apt-get update \
	&& apt-get install -y grafana \
	&& rm -rf /var/lib/apt/lists/*

COPY conf/provisioning /etc/grafana/provisioning

RUN chown -R grafana:grafana /etc/grafana/provisioning /var/lib/grafana

USER grafana

EXPOSE 3010

CMD ["/usr/sbin/grafana-server", "--homepath=/usr/share/grafana", "--config=/etc/grafana/grafana.ini", "--packaging=deb", "cfg:default.paths.provisioning=/etc/grafana/provisioning", "cfg:default.paths.data=/var/lib/grafana"]