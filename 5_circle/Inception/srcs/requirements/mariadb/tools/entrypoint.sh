#!/bin/bash

read_secret() { [ -f "$1" ] && tr -d '\r\n' < "$1"; }
export DB_ROOT_PASSWORD="${DB_ROOT_PASSWORD:-$(read_secret /run/secrets/db_root_password)}"
export DB_PASSWORD="${DB_PASSWORD:-$(read_secret /run/secrets/db_password)}"
export DB_NAME="${DB_NAME}"
export DB_USER="${DB_USER}"

if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "Initializing MariaDB database..."
    mysql_install_db --user=mysql --datadir=/var/lib/mysql
fi

chown -R mysql:mysql /var/lib/mysql
chmod -R 755 /var/lib/mysql

INIT_FILE="/tmp/init.sql"
cat > "$INIT_FILE" << EOF
-- Root 비밀번호 설정
ALTER USER 'root'@'localhost' IDENTIFIED BY '$DB_ROOT_PASSWORD';

-- WordPress 데이터베이스 생성
CREATE DATABASE IF NOT EXISTS \`$DB_NAME\`;

-- WordPress 사용자 생성 및 권한 부여
CREATE USER IF NOT EXISTS '$DB_USER'@'%' IDENTIFIED BY '$DB_PASSWORD';
GRANT ALL PRIVILEGES ON \`$DB_NAME\`.* TO '$DB_USER'@'%';

-- Docker 네트워크에서의 연결을 위한 추가 권한
CREATE USER IF NOT EXISTS '$DB_USER'@'%.inception' IDENTIFIED BY '$DB_PASSWORD';
GRANT ALL PRIVILEGES ON \`$DB_NAME\`.* TO '$DB_USER'@'%.inception';

-- 권한 적용
FLUSH PRIVILEGES;
EOF

chown mysql:mysql "$INIT_FILE"
chmod 644 "$INIT_FILE"

echo "Starting MariaDB with initialization script..."

trap 'rm -f "$INIT_FILE"' EXIT

exec mysqld --user=mysql --init-file="$INIT_FILE"