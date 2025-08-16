FROM debian:bullseye

RUN apt update && apt install -y php php-fpm php-mysql wget unzip curl && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /var/www/wordpress

COPY tools/setup_wp.sh /setup_wp.sh
RUN chmod +x /setup_wp.sh

VOLUME ["/var/www/wordpress"]

ENTRYPOINT ["/setup_wp.sh"]

CMD ["php-fpm", "-F"]
