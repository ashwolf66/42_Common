FROM debian:bookworm

RUN apt-get update && apt-get install -y \
	nginx openssl ca-certificates curl \
	&& rm -rf /var/lib/apt/lists/*

RUN mkdir -p /etc/nginx/ssl && chmod 700 /etc/nginx/ssl

COPY conf/nginx.conf /etc/nginx/nginx.conf
COPY tools/setup_ng.sh /

RUN chmod +x /setup_ng.sh


EXPOSE 443
ENTRYPOINT ["/setup_ng.sh"]
