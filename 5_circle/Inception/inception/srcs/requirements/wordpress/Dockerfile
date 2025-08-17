FROM debian:bullseye

RUN apt update && apt install -y \
    php7.4 php7.4-fpm php7.4-mysql php7.4-curl \
    php7.4-mbstring php7.4-xml php7.4-gd php7.4-zip \
    wget unzip curl && \
    ln -s /usr/sbin/php-fpm7.4 /usr/bin/php-fpm && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir -p /run/php
RUN mkdir -p /var/www/wordpress

COPY tools/setup_wp.sh /setup_wp.sh
RUN chmod +x /setup_wp.sh

VOLUME ["/var/www/wordpress"]
ENTRYPOINT ["/setup_wp.sh"]
