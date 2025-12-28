.PHONY: install dev stop clean re logs test backend-install frontend-install db-migrate build blockchain

##@ 개발 환경

install: ssl backend-install frontend-install db-migrate ## 모든 의존성 설치 및 초기 설정
	@echo "모든 의존성이 설치되었습니다"

ssl: ## SSL 인증서 생성 (없을 경우)
	@if [ ! -d "ssl" ]; then \
		echo "$(YELLOW)SSL 인증서 생성 중...$(NC)"; \
		mkdir -p ssl; \
		openssl req -x509 -newkey rsa:4096 -keyout ssl/key.pem -out ssl/cert.pem -days 365 -nodes -subj "/CN=localhost"; \
		chmod 644 ssl/key.pem; \
		echo "$(GREEN)✓ SSL 인증서가 생성되었습니다$(NC)"; \
	else \
		echo "$(GREEN)✓ SSL 인증서가 이미 존재합니다$(NC)"; \
	fi

backend-install: ## 백엔드 의존성 설치
	@echo "백엔드 의존성 설치 중..."
	@cd backend && npm install
	@echo "백엔드 의존성 설치 완료"

frontend-install: ## 프론트엔드 의존성 설치
	@echo "프론트엔드 의존성 설치 중..."
	@cd frontend && npm install
	@echo "프론트엔드 의존성 설치 완료"

db-migrate: ## 데이터베이스 마이그레이션 실행
	@echo "데이터베이스 마이그레이션 실행 중..."
	@cd database && npm install && node migrate.js
	@echo "데이터베이스 마이그레이션 완료"

blockchain: ## 블록체인 컨트랙트 컴파일
	@echo "블록체인 컨트랙트 컴파일 중..."
	@if command -v npm >/dev/null 2>&1; then \
		cd blockchain && npm install && npx hardhat compile; \
	else \
		echo "npm not found, using docker to compile contracts..."; \
		docker run --rm -v $$(pwd)/blockchain:/app -w /app mirror.gcr.io/library/node:20-alpine /bin/sh -c "npm install && npx hardhat compile"; \
	fi

##@ Docker 명령

dev: ssl blockchain ## Docker Compose로 개발 환경 시작 (백그라운드)
	@echo "개발 환경 시작 중 (백그라운드)..."
	@docker compose up -d --build
	@echo "개발 환경이 백그라운드에서 시작되었습니다"
	@echo "로그 확인: make logs"

stop: ## Docker 컨테이너 중지
	@echo "컨테이너 중지 중..."
	@docker compose down
	@echo "컨테이너가 중지되었습니다"

restart: stop dev ## Docker 컨테이너 재시작

clean: ## Docker 컨테이너 삭제 (데이터베이스 보존)
	@echo "컨테이너 및 임시 파일을 삭제합니다 (데이터베이스 보존)..."
	@docker compose down
	@echo "임시 파일 정리 중..."
	@find . -name ".DS_Store" -delete 2>/dev/null || true
	@find . -name "*.log" -delete 2>/dev/null || true
	@find . -name "*.tmp" -delete 2>/dev/null || true
	@find . -name "__pycache__" -type d -exec rm -rf {} + 2>/dev/null || true
	@find . -name ".pytest_cache" -type d -exec rm -rf {} + 2>/dev/null || true
	@find . -name "*.pyc" -delete 2>/dev/null || true
	@echo "정리 완료 (데이터베이스 보존됨)"

fclean: ## 모든 것 삭제 (데이터베이스, 빌드, 캐시 포함)
	@echo "[경고] 모든 데이터가 삭제됩니다!"
	@echo "5초 후 진행됩니다... (Ctrl+C로 취소)"
	@sleep 5
	@echo "모든 컨테이너, 볼륨, 이미지 및 데이터 삭제 중..."
	@echo "Docker 컨테이너로 데이터베이스 파일 삭제 중..."
	@docker run --rm -v $(shell pwd):/workspace mirror.gcr.io/library/alpine sh -c "rm -rf /workspace/database/*.db /workspace/database/*.db-shm /workspace/database/*.db-wal /workspace/backend/data/*.db* /workspace/backend/database/*.db* 2>/dev/null || true" 2>/dev/null || true
	@docker compose down -v --rmi all --remove-orphans 2>/dev/null || docker compose down -v 2>/dev/null || true
	@echo "남은 데이터베이스 파일 삭제 중..."
	@rm -rf database/*.db database/*.db-shm database/*.db-wal 2>/dev/null || true
	@rm -rf database/ft_transcendence.db* 2>/dev/null || true
	@rm -rf backend/database/*.db* 2>/dev/null || true
	@rm -rf backend/data/*.db* 2>/dev/null || true
	@find . \( -name "*.db" -o -name "*.db-shm" -o -name "*.db-wal" \) ! -path "*/node_modules/*" -delete 2>/dev/null || true
	@echo "빌드 파일 삭제 중..."
	@rm -rf frontend/dist 2>/dev/null || true
	@rm -rf frontend/.vite 2>/dev/null || true
	@rm -rf backend/dist 2>/dev/null || true
	@echo "node_modules 삭제 중..."
	@rm -rf backend/node_modules 2>/dev/null || true
	@rm -rf frontend/node_modules 2>/dev/null || true
	@rm -rf database/node_modules 2>/dev/null || true
	@rm -rf blockchain/node_modules 2>/dev/null || true
	@echo "로그 및 캐시 파일 삭제 중..."
	@rm -rf blockchain/artifacts 2>/dev/null || true
	@rm -rf blockchain/cache 2>/dev/null || true
	@rm -rf backend/uploads/avatars/* 2>/dev/null || true
	@find . -name ".DS_Store" -delete 2>/dev/null || true
	@find . -name "*.log" -delete 2>/dev/null || true
	@find . -name "*.tmp" -delete 2>/dev/null || true
	@find . -name "__pycache__" -type d -exec rm -rf {} + 2>/dev/null || true
	@find . -name ".pytest_cache" -type d -exec rm -rf {} + 2>/dev/null || true
	@find . -name "*.pyc" -delete 2>/dev/null || true
	@find . -name ".npm" -type d -exec rm -rf {} + 2>/dev/null || true
	@echo "Docker 시스템 정리 중..."
	@docker system prune -af --volumes 2>/dev/null || true
	@echo "완전 정리 완료 (모든 데이터 삭제됨)"
	@echo "재시작: make install && make dev"

re: fclean dev ## 완전히 새로 빌드

prune: ## Docker 미사용 리소스 정리 (안전)
	@echo "미사용 Docker 리소스 정리 중..."
	@docker system prune -f 2>/dev/null || true
	@echo "Docker 정리 완료"

logs: ## Docker 로그 표시
	@docker compose logs -f || true

logs-backend: ## 백엔드 로그만 표시
	@docker compose logs -f backend || true

logs-frontend: ## 프론트엔드 로그만 표시
	@docker compose logs -f frontend || true

##@ 빌드 명령

build: ## 프론트엔드 빌드
	@echo "프론트엔드 빌드 중..."
	@cd frontend && npm run build
	@echo "빌드 완료"

##@ 로컬 실행 (Docker 없이)

local-backend: ## 로컬에서 백엔드 실행
	@echo "로컬 백엔드 시작..."
	@cd backend && npm run dev

local-frontend: ## 로컬에서 프론트엔드 실행
	@echo "로컬 프론트엔드 시작..."
	@cd frontend && npm run dev

##@ 테스트 및 유틸리티

check-ports: ## 포트 사용 확인
	@echo "포트 사용 현황:"
	@echo ""
	@echo "포트 3000 (프론트엔드):"
	@lsof -i :3000 || echo "  사용 중이지 않음"
	@echo ""
	@echo "포트 4000 (백엔드):"
	@lsof -i :4000 || echo "  사용 중이지 않음"

env-check: ## 환경 변수 확인
	@if [ ! -f .env ]; then \
		echo "[X] .env 파일이 없습니다"; \
		echo ".env.example을 복사하세요: cp .env.example .env"; \
		exit 1; \
	else \
		echo "[OK] .env 파일이 존재합니다"; \
	fi

status: ## 컨테이너 상태 확인
	@docker compose ps

##@ 데이터베이스

db-reset: ## 데이터베이스 초기화
	@echo "데이터베이스를 초기화합니다..."
	@rm -rf database/*.db database/*.db-shm database/*.db-wal
	@$(MAKE) db-migrate
	@echo "데이터베이스가 초기화되었습니다"

db-backup: ## 데이터베이스 백업
	@echo "데이터베이스 백업 중..."
	@mkdir -p backups
	@cp database/*.db backups/backup-$$(date +%Y%m%d-%H%M%S).db 2>/dev/null || true
	@echo "백업 완료"

##@ 정보

info: env-check ## 프로젝트 정보 표시
	@echo "=== ft_transcendence 프로젝트 정보 ==="
	@echo ""
	@echo "접속 URL:"
	@echo "  프론트엔드 (SPA): https://localhost:3000"
	@echo "  백엔드 API:       https://localhost:4000"
	@echo ""
	@echo "기술 스택:"
	@echo "  백엔드:  Fastify + Node.js + WebSocket"
	@echo "  프론트:  Vanilla JS + Tailwind CSS + Vite"
	@echo "  DB:      SQLite + better-sqlite3"
	@echo "  인증:    JWT + bcrypt + TOTP (2FA)"
	@echo ""
	@echo "선택 모듈 (70점):"
	@echo "  [OK] Backend Framework (Fastify) - 10점"
	@echo "  [OK] Frontend Toolkit (Tailwind) - 5점"
	@echo "  [OK] Database (SQLite) - 5점"
	@echo "  [OK] User Management - 10점"
	@echo "  [OK] Remote Players - 10점"
	@echo "  [OK] 2FA + JWT - 10점"
	@echo "  [OK] AI Opponent - 10점"
	@echo "  [OK] Game customization - 5점"
	@echo "  [OK] Browser Compatibility - 5점"
	@echo ""