FROM debian:bullseye

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y mariadb-servier && rm -rf /var/lib/apt/lists/*

COPY conf/db.cnf /etc/mysql/db.cnf

COPY tools/init_db.sh /docker-entrypoint-initdb.d/init_db.sh
RUN chmod +x /docker-entrypoint-initdb.d/init_db.sh

VOLUME ["/var/lib/mysql"]

EXPOSE 3306

CMD ["mysqld"]
