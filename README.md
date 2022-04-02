# SampleServer

개요
  - IOCP기반 MultiThread Server Engine


설계
  - Contents, AI, Action로 쓰래드 분리
  - Event, Dispatcher를 사용
  - Lock 객체를 따로 두고 DeadLock 방지 설계, 스마트락
  - Packet처리를 데이터 클래스(Tr)과 함수 클래스(Proc)을 나눠 클라이언트, 서버에 불필요한 코드 분리
  - Pool을 사용한 메모리 최적화


![image](https://user-images.githubusercontent.com/17884118/161391417-d59f3eab-8f36-40cf-bfe7-6c98e3f3b5d3.png)
