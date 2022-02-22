#pragma once

#include "Socket.h"
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
	SOCKET&				getSocketHandle();
	const Session_ID&	getSessionId();

public:	// ������ �ʱ�ȭ �Ǵ� �����ö�
	void init();

	// �ı��ɶ�
	void release();

	// pop
	void active();

	// push
	void deactive();

private:
	Session_ID		_id = 0;
	Socket			_socket;
};