#include "TrAuthProc.h"
#include "TrAuth.h"
#include "ActorManager.h"
#include "PlayerActor.h"
#include "SendEvent.h"

// ������ ���̴°� ����. ���ʷ� ������ Ŭ���̾�Ʈ�� ����Ǿ�����
MAKE_PROCESS(TrNetworkConnectReq)
{
	TrNetworkConnectReq* req = static_cast<TrNetworkConnectReq*>(tr);

	{
		// �� ��Ʈ�� �׷��� �ϸ� �ɵ�
	}
}

MAKE_PROCESS(TrNetworkDisConnectReq)
{
	TrNetworkDisConnectReq* req = static_cast<TrNetworkDisConnectReq*>(tr);
	{
		// �� ��Ʈ�� �׷��� �ϸ� �ɵ�
	}
	ActorManager::getInstance()->deletePlayerActor(req->_sessionKey);
}

MAKE_PROCESS(TrActorLoginReq)
{
	TrActorLoginReq* req = static_cast<TrActorLoginReq*>(tr);
	// ����
	{
		// �� ��Ʈ�� �׷��� �ϸ� �ɵ�
	}
}