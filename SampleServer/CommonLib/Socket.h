#pragma once

#include "Base.h"
#include "SocketAddress.h"
#include "PoolItem.h"

#define _WINSOCKAPI_
#include <windows.h>
#include <MSWSock.h>


class OVER_EX {
private:
public:
	WSAOVERLAPPED   over_;
	WSABUF          wsabuf_;
	char            buffer_[1204];
};


class SocketWillDelete
{
public:
	SocketWillDelete();
	SocketWillDelete(const string& address, const int& port);
	~SocketWillDelete();

public:
	// 통신용
	void		init(const string& address, const int& port);
	void		listen();
	const bool	bind();
	const bool	connect();
	const bool	acceptOverlapped(SocketWillDelete* acceptSocket); // accept 준비
	const int	receiveOverlapped(); // overlapeed 수신 준비 ( 백그라운드에서 수신 처리를 함)
	const int	sendOverlapped(); // overlapeed 수신 준비 ( 백그라운드에서 수신 처리를 함)
	// 버퍼 확인용 
	const bool	isOverlapping() const;
	void		setIsOverlapping(const bool isOverlapping);

	const SOCKET& getHandle() const;

	void		getReceiveBuffer(char* outBuffer);
	void		setSendBuffer(const char* sendBuffer);
	SOCKET _socketHandle; // 소켓 핸들
	SocketAddress _address;
	WSABUF _buffer;
	WSABUF _buffer2;
protected:

private:
	static const int MAX_BUFFER_LENGTH = 1024;


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

class Socket : public PoolItem
{
public:
	Socket();
	virtual ~Socket();

public:
	// 생성시 초기화 또는 가져올때
	virtual void init() override final;

	// 파괴될때
	virtual void release() override final;


	// pop
	virtual void active() override final;

	// push
	virtual void deactive() override final;
private:

	SOCKET _handle; // 소켓 핸들
};