#include "TrAuthProc.h"
#include "TrAuth.h"
#include "ActorManager.h"
#include "PlayerActor.h"
#include "SendEvent.h"

#include "SystemManager.h"
#include "ServerNetworkContents.h"

// ������ ���̴°� ����. ���ʷ� ������ Ŭ���̾�Ʈ�� ����Ǿ�����
MAKE_PROCESS(TrNetworkConnectReq)
{
	TrNetworkConnectReq* req = static_cast<TrNetworkConnectReq*>(tr);

	
	{
		// �� ��Ʈ�� �׷��� �ϸ� �ɵ�
	}

	/*Actor* mainActor = SystemManager::getInstance()->getMainActor();
	ServerNetworkContents* networkContents = static_cast<ServerNetworkContents*>(mainActor->getContents(ContentsType::eNetwork));*/
}

MAKE_PROCESS(TrNetworkDisConnectReq)
{
	TrNetworkDisConnectReq* req = static_cast<TrNetworkDisConnectReq*>(tr);
	{
		// �� ��Ʈ�� �׷��� �ϸ� �ɵ�
	}

	Actor* mainActor = SystemManager::getInstance()->getMainActor();
	ServerNetworkContents* networkContents = static_cast<ServerNetworkContents*>(mainActor->getContents(ContentsType::eNetwork));

	networkContents->responseTrNetworkDisConnectReq(req);
}

MAKE_PROCESS(TrActorLoginReq)
{
	TrActorLoginReq* req = static_cast<TrActorLoginReq*>(tr);
	// ����
	{
		// �� ��Ʈ�� �׷��� �ϸ� �ɵ�
	}
}