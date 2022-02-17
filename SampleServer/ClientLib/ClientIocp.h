#pragma once
#include "Iocp.h"

class ClientIocp : public Iocp
{
public:
	ClientIocp();
	virtual ~ClientIocp();

public:
	virtual void runXXX();

	virtual void sendHelloReq();
	virtual void recvTr(Tr* tr);
};

