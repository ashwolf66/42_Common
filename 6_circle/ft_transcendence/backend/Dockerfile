FROM mirror.gcr.io/library/node:20-alpine

WORKDIR /app

# Install dependencies for better-sqlite3 and SSL
RUN apk add --no-cache python3 make g++ openssl

# package.json 복사 및 의존성 설치
COPY package*.json ./
RUN npm install

# 소스 코드 복사
COPY . .

# SSL 디렉토리 생성 및 인증서 자동 생성
RUN mkdir -p /app/ssl && \
    if [ ! -f /app/ssl/cert.pem ] || [ ! -f /app/ssl/key.pem ]; then \
        openssl req -x509 -newkey rsa:4096 \
        -keyout /app/ssl/key.pem -out /app/ssl/cert.pem \
        -days 365 -nodes \
        -subj "/C=KR/ST=Gyeongsan/L=Gyeongsan/O=42gyeongsan/OU=FT_Transcendence/CN=localhost"; \
    fi

# uploads 디렉토리 생성
RUN mkdir -p /app/uploads

EXPOSE 4000

CMD ["npm", "run", "dev"]
