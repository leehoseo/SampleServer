#include "TrAuthProc.h"
#include "TrAuth.h"
#include "ActorManager.h"
#include "PlayerActor.h"
#include "SendEvent.h"

MAKE_PROCESS(TrNetworkConnectReq)
{
	TrNetworkConnectReq* req = static_cast<TrNetworkConnectReq*>(tr);

	{
		// �� ��Ʈ�� �׷��� �ϸ� �ɵ�
	}

	//PlayerActor* newPlayer = ActorManager::getInstance()->createPlayerActor();

	//// ���߿� Ŀ���� ����ü�� ����
	////newPlayer->setName(req->_name);
	////newPlayer->setSessionId(req->_sessionId);
}

MAKE_PROCESS(TrNetworkDisConnectReq)
{
	TrNetworkDisConnectReq* req = static_cast<TrNetworkDisConnectReq*>(tr);
	{
		// �� ��Ʈ�� �׷��� �ϸ� �ɵ�
	}
	ActorManager::getInstance()->deletePlayerActor(req->_sessionId);
}

MAKE_PROCESS(TrActorLoginReq)
{
	TrActorLoginReq* req = static_cast<TrActorLoginReq*>(tr);
	// ����
	{
		// �� ��Ʈ�� �׷��� �ϸ� �ɵ�
	}
}