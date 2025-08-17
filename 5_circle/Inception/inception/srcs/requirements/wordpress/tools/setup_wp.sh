#!/usr/bin/env bash
set -euo pipefail

WP_DIR="/var/www/wordpress"

cd "$WP_DIR"

# 워드프레스 다운로드/배포
if [[ ! -f index.php ]]; then
  echo "[wordpress] Fetching WordPress..."
  wget -q https://wordpress.org/latest.tar.gz
  tar -xzf latest.tar.gz --strip-components=1
  rm -f latest.tar.gz
fi

# wp-config 안전 생성
if [[ ! -f wp-config.php ]]; then
  cp wp-config-sample.php wp-config.php
  sed -i "s/database_name_here/${MYSQL_DATABASE}/" wp-config.php
  sed -i "s/username_here/${MYSQL_USER}/"        wp-config.php
  sed -i "s/password_here/${MYSQL_PASSWORD}/"    wp-config.php
  sed -i "s/localhost/mariadb/"                  wp-config.php
fi

# 퍼미션(필요 시 조정)
chown -R www-data:www-data "$WP_DIR"
find "$WP_DIR" -type d -exec chmod 755 {} \;
find "$WP_DIR" -type f -exec chmod 644 {} \;

echo "[wordpress] Ready."
