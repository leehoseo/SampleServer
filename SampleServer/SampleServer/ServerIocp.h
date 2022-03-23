#pragma once
#include "Iocp.h"

class Session;
class ServerIocp : public Iocp
{
public:
	ServerIocp();
	virtual ~ServerIocp();

public:
	virtual void init();
	virtual void onAccept(Session* acceptSession);
};