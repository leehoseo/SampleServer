#pragma once
#include "NetworkContents.h"
#include "Base.h"
class Session;
class ServerNetworkContents : public NetworkContents
{
public:
	ServerNetworkContents();
	virtual ~ServerNetworkContents();

public:
	void onAccept(Session* acceptSession);

public:
	void sendToClient(Tr* tr, const TickCount64 timer, const std::vector<ActorKey>& actorKeyList);
	void sendToClient(Tr* tr, const TickCount64 timer, const std::vector<SessionKey>& sessionKeyList);
	void sendToClient(Tr* tr, const TickCount64 timer, const ActorKey& actorKey);
	void sendToClient(Tr* tr, const TickCount64 timer, const SessionKey& sessionKey);
};

