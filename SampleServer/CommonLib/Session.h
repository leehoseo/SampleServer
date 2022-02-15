#pragma once

#include "Socket.h"
#include "SocketAddress.h"
#include "Base.h"
#include <winsock2.h>
#include <MSWSock.h>
// 플레이어에 연결되어있는 서버 통신 세션
class Session
{
public:
	Session();
	~Session();

public:
	void				setSocketAddr(const std::string& address, const int& port, const bool isServer);
	SocketAddress&		getSocketAddr();
	SOCKET&				getSocketHandle();
	const SESSION_ID&	getSessionId();

public:	// 생성시 초기화 또는 가져올때
	void init();

	// 파괴될때
	void release();

	// pop
	void active();

	// push
	void deactive();

private:
	SESSION_ID		_id = 0;
	Socket			_socket;
	SocketAddress	_address;
};