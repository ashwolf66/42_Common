# ft_transcendence 프로젝트 구조 - 옵션 C

## 📊 최종 모듈 구성 (70점)

| 모듈 | 타입 | 점수 | 핵심 역할 |
|------|------|------|-----------|
| Backend Framework (Fastify + Node.js) | Major | 10 | REST API + WebSocket 서버 |
| Frontend Toolkit (Tailwind CSS) | Minor | 5 | UI 스타일링 |
| Database (SQLite) | Minor | 5 | 데이터 영속성 |
| Standard User Management | Major | 10 | 유저 시스템 전체 |
| Remote Players | Major | 10 | 원격 대전 |
| 2FA + JWT | Major | 10 | 인증 보안 |
| AI Opponent | Major | 10 | 싱글 플레이 |
| SSR Integration | Minor | 5 | 초기 로딩 최적화 |
| Browser Compatibility | Minor | 5 | 크로스 브라우저 |

**총점: 70점 ✅ (7 Major equivalent)**

---

## 🏗️ 계층 구조 (아키텍처 레벨)

```
Infrastructure Layer (기반)
├── Docker (단일 명령 실행)
├── Fastify (백엔드 프레임워크)
├── Tailwind CSS (프론트엔드 스타일)
└── SQLite (데이터베이스)

Authentication Layer (인증)
├── Standard User Management (기본 유저 시스템)
└── 2FA + JWT (보안 강화)

Game Layer (게임)
├── Mandatory Pong (로컬 2인, 토너먼트)
├── Remote Players (원격 대전)
└── AI Opponent (싱글 플레이)

Enhancement Layer (향상)
├── SSR Integration (성능)
└── Browser Compatibility (접근성)
```

---

## 🔗 모듈 간 의존성 맵

```
Standard User Management
├── 제공: 유저 데이터, 인증 기반
├── 필요: Database, Backend Framework
└── 사용처: Remote Players, 2FA, Tournament

Remote Players
├── 제공: 원격 대전 기능
├── 필요: Backend Framework (WebSocket), User Management
└── 사용처: Tournament (원격 토너먼트 가능)

2FA + JWT
├── 제공: 보안 인증
├── 필요: User Management
└── 사용처: 모든 API 보호

AI Opponent
├── 제공: 혼자 플레이 기능
├── 필요: Game Core
└── 독립적 (다른 모듈에 영향 없음)

SSR Integration
├── 제공: 빠른 초기 로딩
├── 필요: Frontend Framework
└── 선택적 적용 (일부 페이지만)

Browser Compatibility
├── 제공: 더 넓은 브라우저 지원
├── 필요: Frontend 전체
└── 전역 적용
```

---

## 📁 디렉토리 구조 개념

```
프로젝트 루트/
│
├── frontend/ (SPA + SSR)
│   ├── 진입점 (일반 + SSR 전용)
│   ├── 라우터 (SPA 네비게이션)
│   ├── 컴포넌트/
│   │   ├── 인증 관련
│   │   ├── 유저/프로필 관련
│   │   ├── 게임 관련
│   │   ├── 토너먼트 관련
│   │   └── 공통 UI
│   ├── 게임 엔진/
│   │   ├── 코어 (Ball, Paddle, Physics)
│   │   ├── 모드 (Local, Remote, AI)
│   │   ├── AI 로직
│   │   └── 네트워크 (WebSocket 클라이언트)
│   ├── 서비스 (API 통신, 상태 관리)
│   └── 유틸리티
│
├── backend/ (Fastify)
│   ├── 서버 진입점
│   ├── 설정 (DB, JWT, CORS, WebSocket)
│   ├── 라우트 (REST API 엔드포인트)
│   ├── 컨트롤러 (라우트 핸들러)
│   ├── 서비스 (비즈니스 로직)
│   ├── 모델 (데이터베이스 쿼리)
│   ├── WebSocket 핸들러/
│   │   ├── 게임 룸 관리
│   │   ├── 매치메이킹
│   │   └── 실시간 동기화
│   ├── 미들웨어 (인증, 검증, 에러)
│   └── 유틸리티
│
└── database/ (SQLite)
    ├── 스키마 정의
    ├── 마이그레이션
    └── 데이터 파일
```

---

## 🎯 각 모듈의 책임 범위

### 1. Backend Framework (Fastify + Node.js)
- **핵심 역할**: REST API 서버 + WebSocket 서버
- **주요 기능**:
  - RESTful API 엔드포인트 제공
  - WebSocket 실시간 통신
  - 미들웨어 체인 (인증, 검증, 에러 처리)
  - 플러그인 시스템 (JWT, CORS, WebSocket)

### 2. Frontend Toolkit (Tailwind CSS)
- **핵심 역할**: UI 스타일링 프레임워크
- **주요 기능**:
  - Utility-first CSS 접근
  - 반응형 디자인
  - 커스텀 컴포넌트 스타일
  - 일관된 디자인 시스템

### 3. Database (SQLite)
- **핵심 역할**: 데이터 영속성
- **주요 테이블**:
  - users (유저 정보)
  - friendships (친구 관계)
  - games (게임 기록)
  - tournaments (토너먼트)
  - tournament_participants (참가자)
  - user_stats (통계)
- **특징**:
  - 파일 기반 DB (간단한 설정)
  - 트리거로 자동 통계 업데이트
  - Foreign Key 제약 조건

### 4. Standard User Management
- **핵심 역할**: 완전한 유저 시스템
- **주요 기능**:
  - 회원가입/로그인 (bcrypt 해싱)
  - 프로필 관리 (정보, 아바타)
  - 친구 시스템 (요청, 수락, 목록, 온라인 상태)
  - 매치 히스토리 (1v1 기록 저장 및 조회)
  - 유저 통계 (승/패, 승률 등)
- **제공**:
  - 다른 모든 모듈의 기반
  - 토너먼트에 계정 연동
  - Remote Players의 매칭 기반

### 5. Remote Players
- **핵심 역할**: 원격 실시간 대전
- **주요 기능**:
  - WebSocket 기반 실시간 통신
  - 게임 룸 생성 및 관리
  - 서버 권위 게임 상태 동기화
  - 네트워크 문제 처리 (재연결, 지연 보상)
  - 매치메이킹 시스템
- **동기화 전략**:
  - Server-Authoritative 모델
  - 클라이언트는 입력만 전송
  - 서버가 게임 로직 실행
  - 60Hz 상태 브로드캐스트

### 6. 2FA + JWT
- **핵심 역할**: 강화된 인증 보안
- **JWT**:
  - 토큰 기반 인증
  - Stateless 세션
  - API 엔드포인트 보호
  - 짧은 만료 시간 (1시간)
- **2FA (TOTP)**:
  - Time-based One-Time Password
  - QR 코드로 설정
  - Google Authenticator 호환
  - 로그인 시 추가 검증
- **보안**:
  - HTTPS 전용
  - 환경 변수로 Secret 관리
  - Rate limiting

### 7. AI Opponent
- **핵심 역할**: 싱글 플레이 모드
- **제약사항**:
  - A* 알고리즘 금지
  - 키보드 입력 시뮬레이션만 허용
  - 1초에 1번만 게임 상태 확인
  - 인간 수준의 속도
- **구현 방식**:
  - Rule-based 접근
  - 공 궤적 예측 (선형 계산)
  - 벽 튕김 계산
  - 난이도별 오차율 조정
  - 반응 시간 지연 추가
- **난이도**:
  - Easy: 느린 반응, 높은 오차
  - Medium: 중간 반응, 중간 오차
  - Hard: 빠른 반응, 낮은 오차

### 8. SSR Integration
- **핵심 역할**: 초기 로딩 성능 최적화
- **적용 페이지**:
  - 홈 페이지 (SEO)
  - 로그인/회원가입 (SEO)
  - 프로필 페이지 (공개 프로필)
- **비적용 페이지**:
  - 게임 화면 (클라이언트 전용)
  - 실시간 대전 (WebSocket)
- **프로세스**:
  - 서버에서 초기 HTML 생성
  - 초기 상태 포함하여 전송
  - 클라이언트 Hydration
- **장점**:
  - 빠른 First Contentful Paint
  - 향상된 SEO
  - 소셜 미디어 미리보기 지원

### 9. Browser Compatibility
- **핵심 역할**: 넓은 브라우저 지원
- **필수 브라우저**:
  - Firefox (최신 안정 버전) - Mandatory
- **추가 브라우저**:
  - Chrome/Edge (Chromium)
  - Safari (WebKit)
- **구현 전략**:
  - 폴리필 자동 주입
  - 브라우저 기능 감지
  - 대체 UI 제공
  - 크로스 브라우저 테스트
- **감지 기능**:
  - WebSocket 지원
  - Canvas 지원
  - LocalStorage 지원
  - Notification API

---

## 🔄 핵심 플로우

### 인증 플로우
```
회원가입 
→ 로그인 
→ (2FA 활성화 시) 2FA 코드 입력 
→ JWT 발급 
→ 인증 완료
```

### 원격 대전 플로우
```
유저1: 게임 생성 
→ 룸 ID 생성 
→ 유저2: 룸 참가 
→ WebSocket 연결 
→ 게임 시작 
→ 반복: 입력 송신 ↔ 상태 수신 
→ 게임 종료 
→ 결과 DB 저장
```

### AI 대전 플로우
```
난이도 선택 
→ 게임 시작 
→ 반복:
   ├── AI가 1초마다 게임 상태 확인
   ├── 궤적 예측
   ├── 패들 이동 결정
   └── 키보드 입력 시뮬레이션
→ 게임 종료 
→ 결과 저장
```

### 토너먼트 플로우
```
생성 
→ 참가자 등록 (Alias 또는 계정)
→ 대진표 생성
→ 매치 순차 진행
→ 승자 다음 라운드 진출
→ 최종 우승자 결정
```

---

## 🗄️ 데이터베이스 스키마 개념

### 핵심 테이블 구조

**users**
- 기본 정보: id, username, email, password_hash
- 프로필: display_name, avatar_url
- 2FA: two_fa_secret, two_fa_enabled
- 타임스탬프: created_at, updated_at

**friendships**
- 관계: user_id, friend_id
- 상태: pending, accepted, blocked
- 타임스탬프: created_at

**games**
- 참가자: player1_id, player2_id (AI인 경우 null)
- 점수: player1_score, player2_score
- 결과: winner_id
- 메타: game_mode, duration_seconds, tournament_id
- 타임스탬프: started_at, finished_at

**tournaments**
- 정보: name, max_players, current_round
- 상태: pending, active, finished
- 결과: winner_id
- 메타: created_by
- 타임스탬프: created_at, started_at, finished_at

**tournament_participants**
- 관계: tournament_id, user_id
- 순서: seed
- 상태: eliminated
- 타임스탬프: joined_at

**user_stats (denormalized)**
- 집계: total_games, total_wins, total_losses
- 계산: win_rate
- 기록: highest_score, total_playtime_seconds

### 최적화 전략
- 자주 조회하는 컬럼에 인덱스
- 통계는 트리거로 자동 업데이트
- Foreign Key로 데이터 무결성 보장

---

## ⏰ 8주 개발 일정

### Week 1-2: 기반 구축
**목표**: 개발 환경 완성 + Mandatory 구현

- Docker compose 설정
- Fastify 백엔드 기본 구조
- Tailwind 프론트엔드 기본 구조
- SQLite 스키마 설계 및 마이그레이션
- **Mandatory Pong** (로컬 2인, 같은 키보드)
- **토너먼트 시스템** (Alias 입력, 대진표, 순차 진행)

### Week 3: 유저 시스템
**목표**: Standard User Management 완성

- 회원가입/로그인 API (bcrypt)
- JWT 기본 발급
- 프로필 CRUD
- 아바타 업로드
- 친구 시스템 (요청, 수락, 목록)
- 온라인 상태 표시

### Week 4: 보안
**목표**: 2FA + JWT 완성

- JWT 미들웨어 작성
- Protected routes 설정
- 2FA 설정 플로우 (QR 코드)
- TOTP 검증
- 로그인 플로우 수정
- 보안 테스트

### Week 5: 원격 대전
**목표**: Remote Players 완성

- WebSocket 서버 설정
- Connection 핸들러
- 게임 룸 관리 클래스
- 서버 권위 게임 로직
- 실시간 동기화 (60Hz)
- 재연결 처리

### Week 6: AI
**목표**: AI Opponent 완성

- AIPlayer 클래스
- 궤적 예측 알고리즘
- 키보드 시뮬레이션
- 난이도 설정
- 밸런싱
- 매치 히스토리 통합

### Week 7: 최적화
**목표**: SSR + Browser Compatibility

- Vite SSR 설정
- 서버 렌더 함수
- 클라이언트 Hydration
- 폴리필 설정
- 브라우저 감지 및 대체
- 통합 테스트

### Week 8: 마무리
**목표**: Polish & 평가 준비

- UI/UX 개선 (Tailwind)
- 성능 최적화
- 버그 수정
- 문서화 (README, API 문서)
- 데모 시나리오 리허설

---

## 🎭 평가 대비 전략

### 데모 시나리오 (10분)

**1분: 회원가입 + 2FA 설정**
- 회원가입 폼 작성
- 로그인
- 2FA 활성화
- QR 코드 스캔 (Google Authenticator)
- 테스트 코드 입력

**2분: 프로필 및 친구**
- 프로필 페이지 이동
- 아바타 업로드
- 친구 검색 및 추가

**3분: AI 대전**
- AI 모드 선택
- 난이도 선택
- 게임 플레이
- 매치 히스토리 확인

**4분: 원격 대전 준비**
- 두 번째 브라우저 열기
- 두 번째 계정 로그인
- 친구 요청 수락
- 온라인 상태 확인

**5분: 원격 대전**
- 게임 생성 및 초대
- 실시간 대전 (두 브라우저)
- 네트워크 시뮬레이션 (지연)
- 재연결 데모

**6분: 토너먼트**
- 4명 토너먼트 생성
- 대진표 확인
- 매치 진행
- 우승자 결정

### 모듈 정당화 준비

**각 모듈에 대해 설명 준비**:
1. 왜 이 모듈을 선택했는가?
2. 어떻게 구현했는가? (개념적)
3. 다른 모듈과 어떻게 연결되는가?
4. 사용한 라이브러리는? (정당화)

**라이브러리 정당화 예시**:
- `bcrypt`: 비밀번호 해싱만 처리 (전체 인증 시스템 아님) ✅
- `speakeasy`: TOTP 알고리즘만 제공 (전체 2FA 시스템 아님) ✅
- `ws` (WebSocket): 저수준 통신만 제공 (게임 로직은 직접 구현) ✅
- `better-sqlite3`: DB 연결만 제공 (쿼리는 직접 작성) ✅

**금지 예시**:
- `socket.io`: WebSocket + 추가 기능 너무 많음 ❌
- `phaser.js`: 완성된 게임 엔진 ❌
- `passport`: 완성된 인증 시스템 ❌

### 코드 수정 대응

**예상 요청**:
- "게임 속도를 2배로 늘려보세요"
- "AI 난이도를 하나 더 추가해보세요"
- "친구 목록을 이름순으로 정렬해보세요"

**대비 방법**:
- 주요 로직 위치 숙지
- 상수 값 위치 파악
- 빠른 디버깅 능력

---

## 📋 체크리스트

### Mandatory (25%)
- [ ] Docker single command 실행
- [ ] Firefox 최신 버전 호환
- [ ] SPA + 브라우저 네비게이션 (뒤로/앞으로)
- [ ] 로컬 2인 Pong (같은 키보드)
- [ ] 토너먼트 시스템
  - [ ] Alias 입력 (계정 없이)
  - [ ] 대진표 생성
  - [ ] 매치메이킹
  - [ ] 순차 진행
- [ ] 보안
  - [ ] 비밀번호 해싱
  - [ ] SQL injection 방지
  - [ ] XSS 방지
  - [ ] HTTPS/WSS
  - [ ] .env 파일 (git ignore)

### 선택 모듈 (75%)
- [ ] Backend Framework (Fastify + Node.js)
- [ ] Frontend Toolkit (Tailwind CSS)
- [ ] Database (SQLite)
- [ ] Standard User Management
  - [ ] 회원가입/로그인
  - [ ] 프로필 관리
  - [ ] 친구 시스템
  - [ ] 매치 히스토리
  - [ ] 유저 통계
- [ ] Remote Players
  - [ ] WebSocket 서버
  - [ ] 게임 룸 관리
  - [ ] 실시간 동기화
  - [ ] 재연결 처리
- [ ] 2FA + JWT
  - [ ] JWT 인증
  - [ ] 2FA 설정
  - [ ] TOTP 검증
- [ ] AI Opponent
  - [ ] Rule-based AI
  - [ ] 궤적 예측
  - [ ] 난이도 조절
  - [ ] 1초 제약 준수
- [ ] SSR Integration
  - [ ] 서버 렌더링
  - [ ] 클라이언트 Hydration
  - [ ] 일부 페이지 적용
- [ ] Browser Compatibility
  - [ ] Firefox 지원
  - [ ] Chrome/Safari 추가
  - [ ] 폴리필 설정

---

## 🚀 시작하기

### 환경 준비
```
요구사항:
- Docker + Docker Compose
- Git
- 텍스트 에디터/IDE
```

### 초기 설정
1. Repository 생성
2. `.env.example` 복사 → `.env`
3. JWT Secret 생성 및 설정
4. `docker-compose up --build`

### 접속
- Frontend: https://localhost:3000
- Backend API: https://localhost:4000
- WebSocket: wss://localhost:4000/ws/game

---

## 📚 참고 자료

### 공식 문서
- Fastify: https://www.fastify.io/
- Tailwind CSS: https://tailwindcss.com/
- SQLite: https://www.sqlite.org/
- Speakeasy (2FA): https://github.com/speakeasyjs/speakeasy

### 개념 이해
- WebSocket 동기화: Client-Server 게임 아키텍처
- JWT 인증: Stateless authentication
- TOTP: Time-based One-Time Password
- SSR: Server-Side Rendering 개념

---

## ✅ 성공 기준

### 기술적 완성도
- 모든 모듈이 정상 작동
- 버그 없는 안정적 실행
- 보안 요구사항 충족

### 평가 대응
- 명확한 데모 시나리오
- 모듈 정당화 준비
- 코드 수정 능력

### 문서화
- 명확한 README
- 실행 방법 설명
- 모듈 설명 문서

---

**프로젝트 완성을 응원합니다! 🎉**
