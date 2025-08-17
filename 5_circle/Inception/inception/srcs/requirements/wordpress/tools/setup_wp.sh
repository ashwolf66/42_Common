#!/usr/bin/env bash
set -euo pipefail

# =========================
# 환경 변수 (docker-compose .env에서 주입)
# =========================
WP_DIR="/var/www/wordpress"
DB_HOST="${MYSQL_HOST:-mariadb}"
DB_PORT="${MYSQL_PORT:-3306}"
DB_NAME="${MYSQL_DATABASE:?MYSQL_DATABASE not set}"
DB_USER="${MYSQL_USER:?MYSQL_USER not set}"
DB_PASS="${MYSQL_PASSWORD:?MYSQL_PASSWORD not set}"

# =========================
# php-fpm 설정: www.conf 의 listen을 "9000"으로 변경
# =========================
# 배포에 따라 www.conf 위치가 다를 수 있으므로 탐색 후 첫 번째 파일에 적용
CONF_PATH="$(grep -R -l '^\s*\[www\]' /etc/php /usr/local/etc 2>/dev/null | grep '/pool.d/www\.conf' | head -n1 || true)"

if [[ -z "${CONF_PATH}" ]]; then
  echo "[wordpress] ERROR: www.conf not found."
  exit 1
fi

echo "[wordpress] Using FPM pool config: ${CONF_PATH}"

# 1) 기존 listen 라인을 모두 주석 처리(여러 번 등장하는 경우 대비)
sed -ri 's/^\s*listen\s*=.*$/; disabled by setup_wp.sh - was: &/g' "${CONF_PATH}"
# 2) listen = 9000 추가(맨 앞 [www] 섹션 바로 뒤 or 파일 끝)
awk '
  BEGIN {added=0}
  /^\[www\]/ {print; if (!added) {print "listen = 9000"; added=1; next}}
  {print}
  END {if(!added) print "listen = 9000"}
' "${CONF_PATH}" > "${CONF_PATH}.tmp" && mv "${CONF_PATH}.tmp" "${CONF_PATH}"

# 선택: env 전달 이슈 방지(이미 설정돼 있으면 유지)
grep -qE '^\s*clear_env\s*=' "${CONF_PATH}" \
  && sed -ri 's/^\s*clear_env\s*=.*$/clear_env = no/' "${CONF_PATH}" \
  || echo "clear_env = no" >> "${CONF_PATH}"

# =========================
# php-fpm PID/소켓 디렉터리 보장
# =========================
install -d -o www-data -g www-data /run/php

# =========================
# WordPress 코어 다운로드(먼저 수행: index.php 생성 → nginx 403 방지)
# =========================
mkdir -p "${WP_DIR}"
cd "${WP_DIR}"

if [[ ! -f index.php ]]; then
  echo "[wordpress] Fetching WordPress..."
  wget -q https://wordpress.org/latest.tar.gz
  tar -xzf latest.tar.gz --strip-components=1
  rm -f latest.tar.gz
fi

# 퍼미션 정리(읽기/실행에 충분한 기본값)
chown -R www-data:www-data "${WP_DIR}"
find "${WP_DIR}" -type d -exec chmod 755 {} \;
find "${WP_DIR}" -type f -exec chmod 644 {} \;

# =========================
# DB 준비 대기 (포트 열림 + ping 모두 확인)
# =========================
echo "[wordpress] Waiting for MariaDB at ${DB_HOST}:${DB_PORT} ..."
for i in {1..90}; do
  (nc -z "${DB_HOST}" "${DB_PORT}" 2>/dev/null && \
   echo | mysqladmin ping -h"${DB_HOST}" -u"${DB_USER}" -p"${DB_PASS}" --silent 2>/dev/null) && break
  sleep 1
done

# =========================
# wp-config.php 생성/치환 (없을 때만)
# =========================
if [[ ! -f wp-config.php ]]; then
  cp wp-config-sample.php wp-config.php
  sed -i "s/database_name_here/${DB_NAME}/" wp-config.php
  sed -i "s/username_here/${DB_USER}/"      wp-config.php
  sed -i "s/password_here/${DB_PASS}/"      wp-config.php
  sed -i "s/localhost/${DB_HOST}/"          wp-config.php
fi

echo "[wordpress] Ready."

# =========================
# php-fpm 포그라운드 실행
# =========================
exec php-fpm7.4 -F
