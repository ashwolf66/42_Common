## Introduction

이 프로젝트는 Docker 기술을 활용하여 시스템 관리에 대한 지식을 넓히는 것을 목표로 합니다. 여러분은 새로운 개인 가상 머신에서 여러 Docker 이미지를 생성하여 가상화하게 됩니다.

## General guidelines

- 이 프로젝트는 가상 머신(Virtual Machine) 환경에서 완료되어야 합니다.
    
- 프로젝트 설정에 필요한 모든 파일은 **`srcs` 폴더** 내에 위치해야 합니다.
    
- **`Makefile`** 을 반드시 포함해야 하며, 이 파일은 디렉토리 최상위에 위치해야 합니다. 이 파일은 전체 애플리케이션을 설정해야 합니다(즉, docker-compose.yml을 사용하여 Docker 이미지를 빌드해야 합니다).
    
- 이 과제는 사용자의 배경 지식에 따라 익숙하지 않은 개념을 적용해야 할 수 있습니다. 따라서 **Docker 사용법** 및 과제 완료에 도움이 되는 기타 자료를 꼼꼼히 읽어볼 것을 권장합니다.


## Mandatory part

이 프로젝트는 특정 규칙 하에 다양한 서비스로 구성된 소규모 인프라를 가상 머신에서 설정하는 것을 포함합니다. 전체 프로젝트는 Docker Compose를 사용해야 합니다.

각 도커 이미지는 해당 서비스와 동일한 이름을 가져야 합니다.  
각 서비스는 전용 컨테이너에서 실행되어야 합니다.  
성능상의 이유로 컨테이너는 Alpine 또는 Debian의 안정적인 직전 버전(penultimate stable version) 중 하나를 기반으로 빌드되어야 합니다. 선택은 자유롭습니다.
자신의 Dockerfiles를 작성해야 하며(서비스당 하나씩), 이 Dockerfiles는 Makefile을 통해 docker-compose.yml에서 호출되어야 합니다.  
즉, 프로젝트의 도커 이미지를 직접 빌드해야 합니다. 사전 제작된 도커 이미지를 풀(pull)하거나 DockerHub와 같은 서비스를 사용하는 것은 금지됩니다(Alpine/Debian은 이 규칙에서 제외).

다음을 설정해야 합니다:
- TLSv1.2 또는 TLSv1.3만 사용하는 NGINX를 포함하는 도커 컨테이너
    
- php-fpm이 설치 및 구성된 WordPress만 포함하는 도커 컨테이너(nginx 없음)
    
- MariaDB만 포함하는 도커 컨테이너(nginx 없음)
    
- WordPress 데이터베이스를 저장하는 볼륨
    
- WordPress 웹사이트 파일을 저장하는 두 번째 볼륨
    
- 컨테이너 간 연결을 설정하는 도커 네트워크

컨테이너는 충돌 시 자동으로 재시작되어야 합니다.

<span style="background:#40a9ff"> INFO </span>
> Docker 컨테이너는 가상 머신이 아니므로, 컨테이너를 실행할 때 ‘tail -f’와 같은 임시 방편의 패치를 사용하는 것은 권장되지 않습니다. 데몬이 어떻게 동작하는지, 그리고 이를 사용하는 것이 좋은지에 대해 알아보세요.

<span style="background:#ff4d4f"> WARN </span>
> 물론, network: host 또는 --link 또는 links: 사용은 금지되어 있습니다.  
> docker-compose.yml 파일에는 반드시 network 항목이 포함되어야 합니다.  
> 컨테이너는 무한 루프를 실행하는 명령어로 시작되어서는 안 됩니다.  
> 이 규칙은 entrypoint로 사용되는 명령어나 entrypoint 스크립트에 사용되는 명령어에도 적용됩니다.  
> 다음과 같은 임시방편(해키) 패치는 금지됩니다: tail -f, bash, sleep infinity, while true.

<span style="background:#40a9ff"> INFO </span>
> PID 1과 Docker파일 작성 모범 사례에 대해 읽어보세요.

 - 워드프레스 데이터베이스에는 두 명의 사용자가 있어야 하며, 그 중 한 명은 관리자여야 합니다. 관리자의 사용자 이름에는 ‘admin’, ‘Admin’, ‘administrator’, ‘Administrator’(예: admin, administrator, Administrator, admin-123 등)과 같은 단어가 포함되어서는 안 됩니다.

<span style="background:#40a9ff"> INFO </span>
> 볼륨은 Docker를 사용하는 호스트 머신의 /home/login/data 폴더에서 사용할 수 있습니다. 물론 로그인을 사용자 계정으로 바꿔야 합니다.

과정을 단순화하기 위해, 도메인 이름을 로컬 IP 주소를 가리키도록 설정해야 합니다.  
이 도메인 이름은 login.42.fr이어야 하며, 여기서 login에는 본인의 로그인을 사용해야 합니다.  
예를 들어, 로그인 이름이 'wil'이라면 wil.42.fr이 Wil의 웹사이트를 가리키는 IP 주소로 리디렉션됩니다.

<span style="background:#ff4d4f"> WARN </span>
> 최신 태그는 금지되어 있습니다.  
> Dockerfile에 비밀번호를 포함해서는 안 됩니다.  
> 환경 변수의 사용이 필수입니다.  
> 환경 변수를 저장하기 위해 .env 파일을 사용하는 것이 강력히 권장되며, 기밀 정보는 Docker secrets를 사용하여 저장해야 합니다.  
> NGINX 컨테이너는 인프라의 유일한 진입점이어야 하며, 오직 443 포트에서 TLSv1.2 또는 TLSv1.3 프로토콜을 통해서만 접근할 수 있어야 합니다.

다음은 예상 결과의 예시 다이어그램입니다:
![[inception_diagram.png]]

다음은 예상되는 디렉토리 구조의 예입니다:

``` terminel
$> ls -alR
total XX
drwxrwxr-x 3 wil wil 4096 avril 42 20:42 .
drwxrwxrwt 17 wil wil 4096 avril 42 20:42 ..
-rw-rw-r-- 1 wil wil XXXX avril 42 20:42 Makefile
drwxrwxr-x 3 wil wil 4096 avril 42 20:42 secrets
drwxrwxr-x 3 wil wil 4096 avril 42 20:42 srcs
./secrets:
total XX
drwxrwxr-x 2 wil wil 4096 avril 42 20:42 .
drwxrwxr-x 6 wil wil 4096 avril 42 20:42 ..
-rw-r--r-- 1 wil wil XXXX avril 42 20:42 credentials.txt
-rw-r--r-- 1 wil wil XXXX avril 42 20:42 db_password.txt
-rw-r--r-- 1 wil wil XXXX avril 42 20:42 db_root_password.txt
./srcs:
total XX
drwxrwxr-x 3 wil wil 4096 avril 42 20:42 .
drwxrwxr-x 3 wil wil 4096 avril 42 20:42 ..
-rw-rw-r-- 1 wil wil XXXX avril 42 20:42 docker-compose.yml
-rw-rw-r-- 1 wil wil XXXX avril 42 20:42 .env
drwxrwxr-x 5 wil wil 4096 avril 42 20:42 requirements
./srcs/requirements:
total XX
drwxrwxr-x 5 wil wil 4096 avril 42 20:42 .
drwxrwxr-x 3 wil wil 4096 avril 42 20:42 ..
drwxrwxr-x 4 wil wil 4096 avril 42 20:42 bonus
drwxrwxr-x 4 wil wil 4096 avril 42 20:42 mariadb
drwxrwxr-x 4 wil wil 4096 avril 42 20:42 nginx
drwxrwxr-x 4 wil wil 4096 avril 42 20:42 tools
drwxrwxr-x 4 wil wil 4096 avril 42 20:42 wordpress
./srcs/requirements/mariadb:
total XX
drwxrwxr-x 4 wil wil 4096 avril 42 20:45 .
drwxrwxr-x 5 wil wil 4096 avril 42 20:42 ..
drwxrwxr-x 2 wil wil 4096 avril 42 20:42 conf
-rw-rw-r-- 1 wil wil XXXX avril 42 20:42 Dockerfile
-rw-rw-r-- 1 wil wil XXXX avril 42 20:42 .dockerignore
drwxrwxr-x 2 wil wil 4096 avril 42 20:42 tools
[...]
./srcs/requirements/nginx:
total XX
drwxrwxr-x 4 wil wil 4096 avril 42 20:42 .
drwxrwxr-x 5 wil wil 4096 avril 42 20:42 ..
drwxrwxr-x 2 wil wil 4096 avril 42 20:42 conf
-rw-rw-r-- 1 wil wil XXXX avril 42 20:42 Dockerfile
-rw-rw-r-- 1 wil wil XXXX avril 42 20:42 .dockerignore
drwxrwxr-x 2 wil wil 4096 avril 42 20:42 tools
[...]
$> cat srcs/.env
DOMAIN_NAME=wil.42.fr
# MYSQL SETUP
MYSQL_USER=XXXXXXXXXXXX
[...]
$>
```

<span style="background:#ff4d4f"> WARN </span>
> 명백한 보안상의 이유로, 모든 자격 증명, API 키, 비밀번호 등은 반드시 로컬에 다양한 방식이나 파일로 저장하고 git에서 무시해야 합니다. 공개적으로 저장된 자격 증명은 프로젝트의 실패로 직결될 수 있습니다.

<span style="background:#40a9ff"> INFO </span>
> .env와 같은 환경 변수 파일에 변수를 (도메인 이름으로) 저장할 수 있습니다.


## Bonus part

이 프로젝트에서 보너스 파트는 간단하게 설계되어 있습니다.  
각 추가 서비스마다 Dockerfile을 작성해야 합니다. 따라서 각 서비스는 자체 컨테이너에서 실행되며, 필요하다면 전용 볼륨을 갖게 됩니다.

보너스 목록:

- WordPress 웹사이트의 캐시를 적절히 관리할 수 있도록 redis 캐시를 설정하세요.
    
- WordPress 웹사이트의 볼륨을 가리키는 FTP 서버 컨테이너를 설정하세요.
    
- PHP를 제외한 언어로 간단한 정적 웹사이트를 만드세요. 예를 들어, 쇼케이스 사이트나 이력서를 소개하는 사이트 등이 있습니다.
    
- Adminer를 설정하세요.
    
- 유용하다고 생각되는 서비스를 하나 설정하세요. 디펜스(발표) 중에 해당 선택을 정당화해야 합니다.

<span style="background:#40a9ff"> INFO </span>
 > 보너스 부분을 완료하기 위해 추가 서비스를 설정할 수 있습니다. 이 경우 필요에 따라 더 많은 포트를 열 수 있습니다.
 
 <span style="background:#ff4d4f"> WARN </span>
> 보너스 부분은 필수 부분이 완벽하게 완료된 경우에만 평가됩니다. 여기서 완벽하게 완료되었다는 것은 필수 부분이 모두 완료되고 어떠한 오작동도 없이 정상적으로 작동함을 의미합니다. 만약 모든 필수 요구사항을 통과하지 못했다면, 보너스 부분은 전혀 평가되지 않습니다.
