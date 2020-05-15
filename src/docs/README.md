# Mini gateway 의 활용

## 개요
* config
  - 각종 설정 파일
* include
  - 헤더 파일 모음
* library
  - 라이브러리
* proxy
  - TCP/IP의 접속을 유지
  -  internal-message-server(IAS)의 배포 시 클라이언트의 접속과 관계없는 배포가 가능하도록 함
* internal-message-server
  - 실제 메시지 발송 기능 처리
* vendor-kakao
  - 메시지 사업자로 메시지 발송
* third-party
  - 기타 필요한 오픈소스 등의 활용

## 활용 방법
* Vagrant 를 활용하여 가상 머신 상에서 테스트 진행
  - $ vagrant up 
  - $ vagrant ssh
  - (다른 터미널을 이용하여) $ vagrant rsync

* Docker-compose 를 활용하여 일정한 배포 환경 유지
  - $ docker build -t ${image name} .
  - $ docker-compose up
  - ($ docker-compose up -d)
  - ($ docker-compose up --build)
  - $ docker-compose down

