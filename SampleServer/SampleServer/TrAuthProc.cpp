#include "TrAuthProc.h"
#include "TrAuth.h"
#include "ActorManager.h"
#include "PlayerActor.h"
#include "SendEvent.h"

MAKE_PROCESS(TrNetworkConnectReq)
{
	TrNetworkConnectReq* req = static_cast<TrNetworkConnectReq*>(tr);

	{
		// 뭐 스트링 그런거 하면 될듯
	}

	//PlayerActor* newPlayer = ActorManager::getInstance()->createPlayerActor();

	//// 나중에 커지면 구조체로 빼자
	////newPlayer->setName(req->_name);
	////newPlayer->setSessionId(req->_sessionId);
}

MAKE_PROCESS(TrNetworkDisConnectReq)
{
	TrNetworkDisConnectReq* req = static_cast<TrNetworkDisConnectReq*>(tr);
	{
		// 뭐 스트링 그런거 하면 될듯
	}
	ActorManager::getInstance()->deletePlayerActor(req->_sessionId);
}

MAKE_PROCESS(TrActorLoginReq)
{
	TrActorLoginReq* req = static_cast<TrActorLoginReq*>(tr);
	// 검증
	{
		// 뭐 스트링 그런거 하면 될듯
	}
}