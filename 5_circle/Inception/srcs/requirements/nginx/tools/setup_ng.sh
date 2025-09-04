#!/bin/bash

openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/ssl/private/jacha.42.fr.key \
    -out /etc/ssl/certs/jacha.42.fr.crt \
    -subj "/C=KR/ST=Gyeongsangbuk-do/L=Gyeongsan/O=42Gyeongsan/OU=Cadet/CN=jacha.42.fr"

chmod 600 /etc/ssl/private/jacha.42.fr.key
chmod 644 /etc/ssl/certs/jacha.42.fr.crt

exec nginx -g "daemon off;"
