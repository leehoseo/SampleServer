#pragma once

#include "Socket.h"
// �÷��̾ ����Ǿ��ִ� ���� ��� ����
class Session
{
public:
	Session();
	~Session();

private:
	SocketWillDelete _socket;
	SocketAddress _address;
};



