FROM debian:bullseye

RUN apt-get update && apt-get install -y --no-install-recommends \
      nginx openssl ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# 로그를 표준출력/표준오류로
RUN ln -sf /dev/stdout /var/log/nginx/access.log \
 && ln -sf /dev/stderr /var/log/nginx/error.log

# 디렉토리 준비
RUN mkdir -p /var/www/wordpress /etc/nginx/ssl /etc/nginx/conf.d

# 설정/스크립트 복사
COPY conf/default.conf /etc/nginx/conf.d/default.conf
COPY tools/setup_ssl.sh /usr/local/bin/setup_ssl.sh
RUN chmod +x /usr/local/bin/setup_ssl.sh

EXPOSE 443

# 포그라운드 실행
CMD ["/bin/bash", "-lc", "/usr/local/bin/setup_ssl.sh && nginx -g 'daemon off;'"]
