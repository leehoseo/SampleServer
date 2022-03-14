#pragma once
#include "NetworkContents.h"

class Tr;
class ClientNetworkContents : public NetworkContents
{
public:
	ClientNetworkContents();
	virtual ~ClientNetworkContents();

public:
	virtual void recvTr(Tr* tr);
};


