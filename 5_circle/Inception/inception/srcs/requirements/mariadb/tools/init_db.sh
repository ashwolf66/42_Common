#!/bin/bash

mkdir -p /run/mysqld
chown -R mysql:mysql /var/lib/mysql /run/mysqld

if [ ! -d /var/lib/mysql/mysql ]; then
    echo "Initializing database..."
    mysql_install_db --user=mysql > /dev/null

    echo "Creating database and user..."
    mysqld --skip-networking --socket=/tmp/mysql.sock &
    pid="$!"
    sleep 5

    mysql -u root --socket=/tmp/mysql.sock <<EOF
CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';
FLUSH PRIVILEGES;
EOF

    kill "$pid"
    sleep 3
fi

exec mysqld