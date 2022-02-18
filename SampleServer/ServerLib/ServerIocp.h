#pragma once
#include "Iocp.h"

class ServerIocp : public Iocp
{
public:
	ServerIocp();
	virtual ~ServerIocp();

public:
	virtual void runXXX();

	virtual void recvTr(Tr* tr);
};