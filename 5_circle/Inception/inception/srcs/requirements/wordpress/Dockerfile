FROM debian:bullseye

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y php-fpm php-mysql wget unzip curl less && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /var/www/wordpress

COPY tools/setup_wp.sh /setup_wp.sh
RUN chmod +x /setup_wp.sh

VOLUME ["/var/www/wordpress"]

ENTRYPOINT ["/setup_wp.sh"]

CMD ["php-fpm", "-F"]
