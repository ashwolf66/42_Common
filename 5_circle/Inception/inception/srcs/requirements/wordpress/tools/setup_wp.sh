#!/usr/bin/env bash
set -euo pipefail

WP_DIR="/var/www/wordpress"
DB_HOST="${MYSQL_HOST:-mariadb}"
DB_PORT="${MYSQL_PORT:-3306}"
DB_NAME="${MYSQL_DATABASE:?MYSQL_DATABASE not set}"
DB_USER="${MYSQL_USER:?MYSQL_USER not set}"
DB_PASS="${MYSQL_PASSWORD:?MYSQL_PASSWORD not set}"

# php-fpm PID/소켓 디렉토리 보장
install -d -o www-data -g www-data /run/php

# DB 준비 대기 (포트 오픈과 ping 둘 다 시도)
echo "[wordpress] Waiting for MariaDB at ${DB_HOST}:${DB_PORT} ..."
for i in {1..60}; do
  (nc -z "${DB_HOST}" "${DB_PORT}" 2>/dev/null && echo | mysqladmin ping -h"${DB_HOST}" -u"${DB_USER}" -p"${DB_PASS}" --silent 2>/dev/null) && break
  sleep 1
done

cd "$WP_DIR"

# 워드프레스 다운로드/배포
if [[ ! -f index.php ]]; then
  echo "[wordpress] Fetching WordPress..."
  wget -q https://wordpress.org/latest.tar.gz
  tar -xzf latest.tar.gz --strip-components=1
  rm -f latest.tar.gz
fi

# wp-config 안전 생성/치환
if [[ ! -f wp-config.php ]]; then
  cp wp-config-sample.php wp-config.php
  sed -i "s/database_name_here/${DB_NAME}/" wp-config.php
  sed -i "s/username_here/${DB_USER}/"      wp-config.php
  sed -i "s/password_here/${DB_PASS}/"      wp-config.php
  sed -i "s/localhost/${DB_HOST}/"          wp-config.php
fi

# 권한 정리
chown -R www-data:www-data "$WP_DIR"
find "$WP_DIR" -type d -exec chmod 755 {} \;
find "$WP_DIR" -type f -exec chmod 644 {} \;

echo "[wordpress] Ready."
