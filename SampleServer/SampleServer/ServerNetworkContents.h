#pragma once
#include "NetworkContents.h"
#include "Base.h"
class Session;

class TrNetworkDisConnectReq;
class ServerNetworkContents : public NetworkContents
{
public:
	ServerNetworkContents();
	virtual ~ServerNetworkContents();

	void onAccept(Session* acceptSession);
	void onDisconnect(Session* acceptSession);

	void responseTrNetworkDisConnectReq(TrNetworkDisConnectReq* req);

	void sendToActor(Tr* tr, const TickCount64 timer, const std::vector<ActorKey>& actorKeyList);
	void sendToActor(Tr* tr, const TickCount64 timer, const ActorKey& actorKey);

	void sendToActor(Tr* tr, const TickCount64 timer, const std::vector<SessionKey>& sessionKeyList);
	void sendToActor(Tr* tr, const TickCount64 timer, const SessionKey& sessionKey);
};

