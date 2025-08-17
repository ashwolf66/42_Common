FROM debian:bullseye

# PHP 7.4 + FPM + 확장
RUN apt-get update && apt-get install -y --no-install-recommends \
      wget curl ca-certificates \
      php7.4 php7.4-fpm php7.4-mysql php7.4-curl php7.4-mbstring php7.4-xml \
      php7.4-gd php7.4-zip \
    && ln -sf /usr/sbin/php-fpm7.4 /usr/bin/php-fpm \
    && rm -rf /var/lib/apt/lists/*

# 워드프레스용 디렉토리
RUN mkdir -p /var/www/wordpress
WORKDIR /var/www/wordpress

# php-fpm: TCP:9000으로 리슨하도록 수정(유닉스 소켓 금지)
RUN sed -ri 's#^[[:space:]]*listen[[:space:]]*=.*#listen = 0.0.0.0:9000#' /etc/php/7.4/fpm/pool.d/www.conf \
 && sed -ri 's#^;[[:space:]]*clear_env[[:space:]]*=.*#clear_env = no#' /etc/php/7.4/fpm/pool.d/www.conf

# 설치 스크립트
COPY tools/setup_wp.sh /usr/local/bin/setup_wp.sh
RUN chmod +x /usr/local/bin/setup_wp.sh

EXPOSE 9000

# 워드프레스 설치 후 php-fpm 포그라운드
CMD ["/bin/bash", "-lc", "/usr/local/bin/setup_wp.sh && exec php-fpm7.4 -F"]
