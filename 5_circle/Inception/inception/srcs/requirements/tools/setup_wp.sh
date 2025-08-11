#!/bin/bash

cd /var/www/wordpress

if [ ! -f wp-config.php ]; then
	wget https://wordpress.org/latest.tar.gz
	tar -xzf latest.tar.gz --strip-components=1
	rm latest.tar.gz
fi

cp wp-config-sample.php wp-config.php
sed -i "s/database_name_here/${MYSQL_DATABASE}/" wp-config.php
sed -i "s/username_here/${MYSQL_USER}/" wp-config.php
sed -i "s/password_here/${MYSQL_PASSWORD}/" wp-config.php
sed -i "s/localhost/mariadb/" wp-config.php

exec "$@"
