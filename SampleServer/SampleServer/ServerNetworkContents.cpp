#include "ServerNetworkContents.h"
#include "Session.h"
#include "PlayerActor.h"
#include "ActorManager.h"
#include "TrAuth.h"
#include "SendEvent.h"
#include "SystemManager.h"
#include "Dispatcher.h"
#include "Logger.h"

ServerNetworkContents::ServerNetworkContents()
{
}

ServerNetworkContents::~ServerNetworkContents()
{
}

void ServerNetworkContents::onAccept(Session* acceptSession)
{
	// ���������� PlayerActor �̸� �����صд�.
	PlayerActor* newPlayerActor = ActorManager::getInstance()->createPlayerActor();
	newPlayerActor->setSessionKey(acceptSession->getSessionKey());

	TrNetworkConnectAck* ack = new TrNetworkConnectAck();
	ack->set(newPlayerActor->getActorKey());
	sendToActor(ack, 0, acceptSession->getSessionKey());
}

void ServerNetworkContents::onDisconnect(Session* acceptSession)
{
	// ActorManager�� ���� Erease ó���� �߰��ؾ��Ѵ�.
	TrNetworkDisConnectReq req;
	req.set(acceptSession->getSessionKey());

	responseTrNetworkDisConnectReq(&req);
}

void ServerNetworkContents::responseTrNetworkDisConnectReq(TrNetworkDisConnectReq* req)
{
	SessionKey deleteSessionKey;
	if (true == req->_actorKey.isValid())
	{
		ActorManager::getInstance()->getPlayerSessionKey(req->_actorKey, deleteSessionKey);
	}
	else if (true == req->_sessionKey.isValid())
	{
		deleteSessionKey = req->_sessionKey;
	}
	else
	{
		// �ַ��äääää�
		return;
	}

	ActorManager::getInstance()->deletePlayerActor(deleteSessionKey);
	Iocp* iocp = SystemManager::getInstance()->getIcop();
	iocp->deleteSession(deleteSessionKey);

	std::string str = "Disconnect Clients ID: " + std::to_string(req->_sessionKey.get());
	Logger::getInstance()->log(Logger::Level::DEBUG, str);
}

void ServerNetworkContents::sendToActor(Tr* tr, const TickCount64 timer, const std::vector<ActorKey>& actorKeyList)
{
	std::vector<SessionKey> sessionKeyList;
	ActorManager::getInstance()->getPlayerSessionKey(actorKeyList, sessionKeyList);

	SendEvent* sendEvent = new SendEvent(tr, timer, sessionKeyList);
	Dispatcher::getInstance()->push(sendEvent);
}

void ServerNetworkContents::sendToActor(Tr* tr, const TickCount64 timer, const std::vector<SessionKey>& sessionKeyList)
{
	SendEvent* sendEvent = new SendEvent(tr, timer, sessionKeyList);
	Dispatcher::getInstance()->push(sendEvent);
}

void ServerNetworkContents::sendToActor(Tr* tr, const TickCount64 timer, const ActorKey& actorKey)
{
	SessionKey sessionKey;
	ActorManager::getInstance()->getPlayerSessionKey(actorKey, sessionKey);

	SendEvent* sendEvent = new SendEvent(tr, timer, sessionKey);
	Dispatcher::getInstance()->push(sendEvent);
}

void ServerNetworkContents::sendToActor(Tr* tr, const TickCount64 timer, const SessionKey& sessionKey)
{
	SendEvent* sendEvent = new SendEvent(tr, timer, sessionKey);
	Dispatcher::getInstance()->push(sendEvent);
}