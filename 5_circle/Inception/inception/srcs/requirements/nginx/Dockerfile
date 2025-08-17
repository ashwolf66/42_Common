FROM debian:bullseye

RUN apt update && \
    apt install -y nginx openssl && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir -p /var/www/wordpress

COPY tools/setup_ssl.sh /setup_ssl.sh
RUN chmod +x /setup_ssl.sh && /setup_ssl.sh

COPY conf/default.conf /etc/nginx/conf.d/default.conf

VOLUME ["/var/www/wordpress"]

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]