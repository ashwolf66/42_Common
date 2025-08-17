#!/usr/bin/env bash
set -euo pipefail

CRT="/etc/nginx/ssl/selfsigned.crt"
KEY="/etc/nginx/ssl/selfsigned.key"
DOMAIN="${DOMAIN_NAME:-jacha.42.fr}"

if [[ ! -f "$CRT" || ! -f "$KEY" ]]; then
  openssl req -x509 -nodes -newkey rsa:2048 \
    -keyout "$KEY" \
    -out "$CRT" \
    -days 3650 \
    -subj "/C=KR/ST=Seoul/L=Seoul/O=Inception/OU=Dev/CN=jacha.42.fr"
fi

