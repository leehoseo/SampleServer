#pragma once
#include "NetworkContents.h"

class Tr;
class ServerNetworkContents : public NetworkContents
{
public:
	ServerNetworkContents();
	virtual ~ServerNetworkContents();

public:
	virtual void recvTr(Tr* tr);
};

