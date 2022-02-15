#pragma once

#include "Socket.h"
#include "SocketAddress.h"
#include "Base.h"
#include <winsock2.h>
#include <MSWSock.h>
// �÷��̾ ����Ǿ��ִ� ���� ��� ����
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

public:	// ������ �ʱ�ȭ �Ǵ� �����ö�
	void init();

	// �ı��ɶ�
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