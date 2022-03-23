#include "ServerNetworkContents.h"
#include "Session.h"
#include "PlayerActor.h"
#include "ActorManager.h"
#include "TrAuth.h"
#include "SendEvent.h"
#include "SystemManager.h"
#include "Dispatcher.h"

ServerNetworkContents::ServerNetworkContents()
{
}

ServerNetworkContents::~ServerNetworkContents()
{
}

void ServerNetworkContents::onAccept(Session* acceptSession)
{
	// 접속했을때 PlayerActor 미리 생성해둔다.
	PlayerActor* newPlayerActor = ActorManager::getInstance()->createPlayerActor();
	newPlayerActor->setSessionKey(acceptSession->getSessionKey());

	TrNetworkConnectAck ack;
	ack.set(newPlayerActor->getActorKey());
	sendToActor(&ack, 0, newPlayerActor->getActorKey());
}

void ServerNetworkContents::sendToActor(Tr* tr, const TickCount64 timer, const std::vector<ActorKey>& actorKeyList)
{
	//SendEvent* sendEvent = new SendEvent(tr, timer, sessionIdList);
	//Dispatcher::getInstance()->push(sendEvent);
}

void ServerNetworkContents::sendToActor(Tr* tr, const TickCount64 timer, const std::vector<SessionKey>& sessionKeyList)
{
	SendEvent* sendEvent = new SendEvent(tr, timer, sessionKeyList);
	Dispatcher::getInstance()->push(sendEvent);
}

void ServerNetworkContents::sendToActor(Tr* tr, const TickCount64 timer, const ActorKey& actorKey)
{
	//SendEvent* sendEvent = new SendEvent(tr, timer, sessionId);
	//Dispatcher::getInstance()->push(sendEvent);
}

void ServerNetworkContents::sendToActor(Tr* tr, const TickCount64 timer, const SessionKey& sessionKey)
{
	SendEvent* sendEvent = new SendEvent(tr, timer, sessionKey);
	Dispatcher::getInstance()->push(sendEvent);
}

void ServerNetworkContents::sendToAllActor()
{
}
