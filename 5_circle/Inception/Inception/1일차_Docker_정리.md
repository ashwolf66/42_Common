
# Docker & Docker Compose 정리 (1일차 학습)

---

## Docker란?

- Docker는 컨테이너 기술을 활용하여 소프트웨어를 **격리된 환경에서 실행**할 수 있도록 해주는 오픈소스 플랫폼이다.
- 기존 가상머신(VM)과 달리 전체 운영체제를 가상화하지 않고, **호스트 운영체제의 커널을 공유**하여 가볍고 빠르게 동작한다.
- 여러 개의 컨테이너를 한 대의 서버에서 효율적으로 구동할 수 있다.
- 동일한 환경을 다양한 시스템에 배포할 수 있어 **개발, 테스트, 배포의 일관성**을 확보할 수 있다.

---

## Docker와 VM의 차이점

| 항목 | Docker | VM (Virtual Machine) |
|------|--------|-----------------------|
| 구조 | 호스트 OS 커널을 공유 | 독립된 OS 실행 |
| 무게 | 가볍고 빠름 | 무겁고 느림 |
| 자원 사용 | 적음 | 많음 |
| 부팅 속도 | 수 초 내 실행 | 수 분 소요 가능 |
| 실행 단위 | 컨테이너 | 가상머신 (전체 OS) |
| 활용 목적 | 마이크로서비스, 배포 자동화 | 복잡한 OS 환경 필요 시 |

---

## 이미지와 컨테이너 개념

### 이미지 (Image)
- 컨테이너 생성을 위한 **불변의 실행 환경 템플릿**이다.
- OS 레이어, 애플리케이션, 설정 파일 등을 포함한다.
- 직접 실행되지 않으며, 컨테이너를 만들기 위한 기반으로 사용된다.
- 여러 계층(layer)으로 구성되어 효율적인 저장이 가능하다.

### 컨테이너 (Container)
- 이미지를 기반으로 실행된 **독립된 인스턴스**이다.
- 읽기/쓰기 가능한 실행 환경으로, 실제 애플리케이션이 동작하는 공간이다.
- 일시적으로 존재하며 삭제 시 데이터가 사라질 수 있다 (지속 데이터는 볼륨 사용).
- 컨테이너는 이미지를 실행해야 생성되며, 이미지는 컨테이너 없이도 존재 가능하다.

---

## docker-compose.yml 구성 요소

Docker Compose는 `.yml` 확장자를 가진 설정 파일을 기반으로 동작한다. 이 파일은 여러 컨테이너를 하나의 서비스처럼 관리할 수 있게 해주며, 아래와 같은 주요 구성 요소를 포함한다.

---

### 1. 버전 정의

```yaml
version: '3.8'
```

- `version`: `docker-compose.yml` 파일의 문법 버전을 정의한다.
- Docker Engine의 버전에 따라 지원되는 Compose 버전이 다르므로, 사용하는 Docker 환경에 맞게 **최신 안정 버전**을 선택해야 한다.

---

### 2. 서비스 정의

```yaml
services:
  web:
    image: nginx:latest
    ports:
      - "80:80"
    environment:
      - APP_ENV=production
    command: ["nginx", "-g", "daemon off;"]
    depends_on:
      - db
    build:
      context: ./web
      dockerfile: Dockerfile
```

- `services`: 하나 이상의 컨테이너를 묶어 관리하는 단위이다. 각 서비스는 하나의 컨테이너 인스턴스를 나타낸다.

#### 서비스 항목 내 주요 옵션

| 옵션 | 설명 |
|------|------|
| `image` | 사용할 Docker 이미지의 이름을 지정한다. 로컬에 없으면 Docker Hub에서 자동으로 pull 된다. |
| `build` | Dockerfile을 사용하여 이미지를 직접 빌드할 수 있도록 설정. `context`, `dockerfile`을 하위에 포함 |
| `command` | 컨테이너 시작 시 실행될 명령어를 설정한다. |
| `environment` | 컨테이너 내부에서 사용할 환경변수를 지정한다. |
| `depends_on` | 의존성을 가지는 다른 서비스(컨테이너)를 먼저 실행하도록 설정한다. |
| `ports` | 호스트 포트와 컨테이너 포트를 바인딩한다. `"호스트:컨테이너"` 형식 |
| `extends` | 다른 `yml` 또는 같은 파일에서 정의된 속성을 상속받는다. (Compose v3에서는 제한적 지원) |
<span style="background:#ff4d4f"> WARN </span>
>links`: 더 이상 사용 권장되지 않으며, 사용자 정의 네트워크(`networks`)를 사용하는 방식으로 대체되었다.

---

### 3. 네트워크 정의

```yaml
networks:
  my_network:
    driver: bridge
    ipam:
      config:
        - subnet: "172.20.0.0/16"
    external: false
```

- `networks`: 컨테이너 간 통신을 구성하는 사용자 정의 네트워크를 설정한다.

#### 주요 네트워크 옵션

| 옵션 | 설명 |
|------|------|
| `driver` | 사용할 네트워크 드라이버를 정의한다. 기본값은 `bridge` |
| `ipam` | IP 주소 관리 옵션으로, 서브넷, IP 범위 등을 설정할 수 있다. |
| `external` | true로 설정 시, 새 네트워크를 생성하지 않고 기존에 정의된 네트워크를 사용한다. |

---

### 4. 볼륨 정의

```yaml
volumes:
  db_data:
    driver: local
    external: false
```

- `volumes`: 컨테이너 데이터의 영속성을 위해 사용하는 저장소를 정의한다.

#### 주요 볼륨 옵션

| 옵션 | 설명 |
|------|------|
| `driver` | 사용할 볼륨 드라이버를 지정한다. 일반적으로 `local` 사용 |
| `external` | true로 설정 시, 이미 존재하는 외부 볼륨을 사용하도록 지정한다. false면 새로 생성된다. |

---

### 5. 환경변수 파일 `.env`

Docker Compose에서는 `.env` 파일을 통해 환경변수를 외부에서 정의하고, `docker-compose.yml` 내에서 변수처럼 사용할 수 있다.

#### 예시: `.env`

```env
DOMAIN_NAME=login.42.fr
MYSQL_ROOT_PASSWORD=supersecret
MYSQL_USER=myuser
MYSQL_PASSWORD=mypassword
```

#### 예시: docker-compose.yml

```yaml
services:
  wordpress:
    image: wordpress:latest
    environment:
      WORDPRESS_DB_HOST: mariadb:3306
      WORDPRESS_DB_USER: ${MYSQL_USER}
      WORDPRESS_DB_PASSWORD: ${MYSQL_PASSWORD}
```

#### `.env` 사용의 장점

| 항목 | 설명 |
|------|------|
| 보안성 | 비밀번호, 키 등을 직접 yml 파일에 노출하지 않고 분리 |
| 재사용성 | 환경 별 설정값 변경이 용이 |
| 유지보수성 | 한 곳에서 값을 관리하므로 수정이 간편 |
| Git 관리 | `.env`는 `.gitignore`에 등록하여 민감정보 유출 방지 가능 |

#### 주의사항

- `.env`는 `docker-compose.yml`과 **같은 디렉토리**에 있어야 자동으로 인식된다.
- 변수명은 쉘 환경 변수 스타일로 `KEY=value` 형식이어야 한다.
- `yml`에서는 반드시 `${변수명}` 형태로 참조해야 한다.

---

## 기타 팁

- `.env` 파일을 통해 민감 정보(비밀번호, 키 등) 외부화 가능
- `Makefile`과 함께 사용하면 자동화된 빌드 및 배포 가능
- 네트워크 설정은 `network_mode`, `networks` 등을 활용해 사용자 정의 가능
- `restart: always`로 컨테이너 자동 재시작 설정 가능
