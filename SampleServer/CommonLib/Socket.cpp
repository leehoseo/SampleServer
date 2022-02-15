#include "Socket.h"

#pragma optimize ("" , off )
Socket::Socket()
{
	_handle = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);	// windows

	{
		// https://snowfleur.tistory.com/193?category=756631
		// Page Locking 최소화를 위해 송 수신 버퍼를 0으로 설정함
		// 커널 레벨에서의 송수신버퍼를 이용하지 않고 애플리케이션에서 제공하는 버퍼로 바로 복사를 해버리기 때문에 
		// 복사 횟수가 한 번 줄어 속도가 굉장히 빨라진다.
		int zero = 0;
		setsockopt(_handle, SOL_SOCKET, SO_SNDBUF, (char*)&zero, sizeof(zero));
		setsockopt(_handle, SOL_SOCKET, SO_RCVBUF, (char*)&zero, sizeof(zero));
	}
}

Socket::~Socket()
{
	closesocket(_handle);
}

SOCKET& Socket::getHandle()
{
	return _handle;
}
