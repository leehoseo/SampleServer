#pragma once

#include "Base.h"
#include "SocketAddress.h"

#define _WINSOCKAPI_
#include <windows.h>
#include <MSWSock.h>

class Socket
{
public:
	Socket();
	Socket(const string& address, const uint8_t& port);
	~Socket();

public:
	// 통신용
	void		init(const string& address, const uint8_t& port);
	void		listen();
	const bool	bind();
	const bool	connect();
	const bool	acceptOverlapped(Socket& acceptSocket); // accept 준비
	const int	receiveOverlapped(); // overlapeed 수신 준비 ( 백그라운드에서 수신 처리를 함)
	const int	sendOverlapped(); // overlapeed 수신 준비 ( 백그라운드에서 수신 처리를 함)
	const int	updateAcceptContext(Socket& listenSocket);
	// 버퍼 확인용 
	const bool	isOverlapping() const;
	void		setIsOverlapping(const bool isOverlapping);

	const SOCKET& getHandle() const;

	void		getReceiveBuffer(char* outBuffer);
	void		setSendBuffer(const char* sendBuffer);
protected:
	SOCKET _socketHandle; // 소켓 핸들

private:
	static const int MAX_BUFFER_LENGTH = 1024;

	SocketAddress _address;

	// AcceptEx 함수 포인터
	LPFN_ACCEPTEX _acceptExFunc = nullptr;

	// I/O중인지
	bool _isOverlapping = false;

	// Overlapped receive or accept을 할 때 사용되는 overlapped 객체입니다. 
	// I/O 완료 전까지는 보존되어야 합니다.
	WSAOVERLAPPED _receiveOverlappedBuffer;
	// overlapped 수신을 하는 동안 여기에 recv의 flags에 준하는 값이 채워집니다.
	// overlapped I/O가 진행되는 동안 이 값을 건드리지 마세요.
	DWORD _readFlags = 0;

	char _receiveBuffer[MAX_BUFFER_LENGTH];
	char _sendBuffer[MAX_BUFFER_LENGTH];
};
