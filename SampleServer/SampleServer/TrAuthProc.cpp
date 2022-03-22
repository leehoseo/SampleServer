#include "TrAuthProc.h"
#include "TrAuth.h"
#include "ActorManager.h"
#include "PlayerActor.h"
#include "SendEvent.h"

void TrNetworkConnectReqProc::process(Tr* tr)
{
	TrNetworkConnectReq* req = static_cast<TrNetworkConnectReq*>(tr);

	// ����
	{
		// �� ��Ʈ�� �׷��� �ϸ� �ɵ�
	}

	// ���ο� �÷��̾� ����
	PlayerActor* newPlayer = ActorManager::getInstance()->createPlayerActor();

	// �ʱ�ȭ
	// ���߿� Ŀ���� ����ü�� ����
	newPlayer->setName(req->_name);
	newPlayer->setSessionId(req->_sessionId);

	// ���� ������ �ٽ� Ŭ���̾�Ʈ���� �����ش�.
	{
		TrNetworkConnectAck* ack = new TrNetworkConnectAck();
		ack->set(newPlayer->getActorKey());
		makeSendEventToClient(ack, 0, newPlayer->getSessionId());
	}

	// �ٸ� �÷��̾�鿡�� actor�� �����϶�� ��û�� ����
	{
		std::vector<Session_ID> sessionIdList;
		ActorManager::getInstance()->getActivePlayerActorSessionIds(sessionIdList);

		TrActorLoginAck* ack = new TrActorLoginAck();
		ack->set(newPlayer->getActorKey(), newPlayer->getName().c_str());
		makeSendEventToClient(ack, 0, sessionIdList);
	}
}

void TrNetworkDisConnectReqProc::process(Tr* tr)
{
	TrNetworkDisConnectReq* req = static_cast<TrNetworkDisConnectReq*>(tr);

	// ����
	{
		// �� ��Ʈ�� �׷��� �ϸ� �ɵ�
	}

	// ���ο� �÷��̾� ����
	ActorManager::getInstance()->deletePlayerActor(req->_sessionId);
}
