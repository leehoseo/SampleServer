#include "TrAuthProc.h"
#include "TrAuth.h"
#include "ActorManager.h"
#include "PlayerActor.h"
#include "SendEvent.h"

void TrNetworkConnectReqProc::process(Tr* tr)
{
	TrNetworkConnectReq* req = static_cast<TrNetworkConnectReq*>(tr);

	// 검증
	{
		// 뭐 스트링 그런거 하면 될듯
	}

	// 새로운 플레이어 생성
	PlayerActor* newPlayer = ActorManager::getInstance()->createPlayerActor();

	// 초기화
	// 나중에 커지면 구조체로 빼자
	newPlayer->setName(req->_name);
	newPlayer->setSessionId(req->_sessionId);

	// 접속 정보를 다시 클라이언트에게 보내준다.
	{
		TrNetworkConnectAck* ack = new TrNetworkConnectAck();
		ack->set(newPlayer->getActorKey());
		makeSendEventToClient(ack, 0, newPlayer->getSessionId());
	}

	// 다른 플레이어들에게 actor를 생성하라는 요청을 보냄
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

	// 검증
	{
		// 뭐 스트링 그런거 하면 될듯
	}

	// 새로운 플레이어 생성
	ActorManager::getInstance()->deletePlayerActor(req->_sessionId);
}
