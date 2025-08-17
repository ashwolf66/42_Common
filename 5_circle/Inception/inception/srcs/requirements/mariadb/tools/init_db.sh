#!/usr/bin/env bash
set -euo pipefail

DATADIR="/var/lib/mysql"
RUN_DIR="/run/mysqld"
mkdir -p "$RUN_DIR" && chown -R mysql:mysql "$RUN_DIR" "$DATADIR"

# 1) 데이터 디렉터리 비어 있으면 초기화
if [ ! -d "$DATADIR/mysql" ]; then
  echo "[mariadb] Initializing datadir..."
  mariadb-install-db --user=mysql --datadir="$DATADIR" --skip-test-db --rpm
  INIT_SQL="/tmp/init.sql"
  cat > "$INIT_SQL" <<SQL
CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\` CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
FLUSH PRIVILEGES;
SQL
  echo "[mariadb] Applying init SQL via bootstrap..."
  mysqld --user=mysql --datadir="$DATADIR" --skip-networking=1 --socket="$RUN_DIR/mysqld.sock" --bootstrap < "$INIT_SQL"
fi

# 2) 포그라운드 실행 (PID 1)
echo "[mariadb] Starting server..."
exec mysqld --user=mysql --datadir="$DATADIR" --pid-file="$RUN_DIR/mysqld.pid"
