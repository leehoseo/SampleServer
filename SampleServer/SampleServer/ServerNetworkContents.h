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
	void sendToActor(Tr* tr, const TickCount64 timer, const std::vector<ActorKey>& actorKeyList);
	void sendToActor(Tr* tr, const TickCount64 timer, const ActorKey& actorKey);

	void sendToActor(Tr* tr, const TickCount64 timer, const std::vector<SessionKey>& sessionKeyList);
	void sendToActor(Tr* tr, const TickCount64 timer, const SessionKey& sessionKey);

	// field ������ �ֱ� �ؾ��Ұ� ����
	void sendToAllActor();
};

