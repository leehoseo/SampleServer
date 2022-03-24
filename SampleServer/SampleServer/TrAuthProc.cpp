#include "TrAuthProc.h"
#include "TrAuth.h"
#include "ActorManager.h"
#include "PlayerActor.h"
#include "SendEvent.h"

#include "SystemManager.h"
#include "ServerNetworkContents.h"

// 지금은 쓰이는곳 없다. 최초로 서버와 클라이언트가 연결되었을때
MAKE_PROCESS(TrNetworkConnectReq)
{
	TrNetworkConnectReq* req = static_cast<TrNetworkConnectReq*>(tr);

	
	{
		// 뭐 스트링 그런거 하면 될듯
	}

	/*Actor* mainActor = SystemManager::getInstance()->getMainActor();
	ServerNetworkContents* networkContents = static_cast<ServerNetworkContents*>(mainActor->getContents(ContentsType::eNetwork));*/
}

MAKE_PROCESS(TrNetworkDisConnectReq)
{
	TrNetworkDisConnectReq* req = static_cast<TrNetworkDisConnectReq*>(tr);
	{
		// 뭐 스트링 그런거 하면 될듯
	}

	Actor* mainActor = SystemManager::getInstance()->getMainActor();
	ServerNetworkContents* networkContents = static_cast<ServerNetworkContents*>(mainActor->getContents(ContentsType::eNetwork));

	networkContents->responseTrNetworkDisConnectReq(req);
}

MAKE_PROCESS(TrActorLoginReq)
{
	TrActorLoginReq* req = static_cast<TrActorLoginReq*>(tr);
	// 검증
	{
		// 뭐 스트링 그런거 하면 될듯
	}
}