FROM debian:bullseye

# 기본 패키지 & PHP 7.4 + FPM + 확장 + MariaDB 클라이언트(대기/점검용)
RUN apt-get update && apt-get install -y --no-install-recommends \
      ca-certificates wget curl \
      mariadb-client netcat \
      php7.4 php7.4-fpm php7.4-mysql php7.4-curl php7.4-mbstring php7.4-xml \
      php7.4-gd php7.4-zip \
 && ln -sf /usr/sbin/php-fpm7.4 /usr/bin/php-fpm \
 && rm -rf /var/lib/apt/lists/*

# 워드프레스 디렉터리
RUN mkdir -p /var/www/wordpress
WORKDIR /var/www/wordpress

# php-fpm을 TCP:9000으로 리슨 (유닉스 소켓 금지) + env 전달
RUN sed -ri 's#^[[:space:]]*listen[[:space:]]*=.*#listen = 0.0.0.0:9000#' /etc/php/7.4/fpm/pool.d/www.conf \
 && sed -ri 's#^;[[:space:]]*clear_env[[:space:]]*=.*#clear_env = no#' /etc/php/7.4/fpm/pool.d/www.conf

# PID/소켓 경로 보장 (컨테이너 부팅 시 다시 생성되지만 안전장치)
RUN mkdir -p /run/php && chown -R www-data:www-data /run/php

# 설치 스크립트 복사
COPY tools/setup_wp.sh /usr/local/bin/setup_wp.sh
RUN chmod +x /usr/local/bin/setup_wp.sh

EXPOSE 9000

# 워드프레스 설치/설정 후 php-fpm을 포그라운드로 실행
CMD ["/bin/bash", "-lc", "/usr/local/bin/setup_wp.sh && exec php-fpm7.4 -F"]
