# SampleServer

개요
  - IOCP기반 MultiThread Server Engine


다이어그램

![image](https://user-images.githubusercontent.com/17884118/161391417-d59f3eab-8f36-40cf-bfe7-6c98e3f3b5d3.png)

 - Contents로 여러 컨텐츠 관리 ( NetworkContents, ThreadContents, GuildContents 등등 )
 - Actor에 ContentsList를 두고 필요한 Contents를 insert해서 관리
 - Packet처리를 데이터 클래스(Tr)과 함수 클래스(Proc)을 나눠 클라이언트, 서버에 불필요한 코드 분리
 - Contents, AI, Action로 쓰래드 분리 ( TrThread )
 - Event, Dispatcher, TrQueueManager를 사용 원하는 Thread에 맡김

