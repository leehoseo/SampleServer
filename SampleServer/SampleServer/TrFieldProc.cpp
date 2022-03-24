#include "TrFieldProc.h"
#include "TrField.h"
#include "PlayerActor.h"
#include "ServerFieldContents.h"
#include "ActorManager.h"

MAKE_PROCESS(TrLoginToLobbyReq)
{
	TrLoginToLobbyReq* req = static_cast<TrLoginToLobbyReq*>(tr);
	{
		// �� ��Ʈ�� �׷��� �ϸ� �ɵ�
	}

	PlayerActor* player = ActorManager::getInstance()->getPlayerActor(req->_actorKey);

	ServerFieldContents* fieldContents = static_cast<ServerFieldContents*>(player->getContents(ContentsType::eField));
	fieldContents->responseTrLoginToLobbyReq(req);
}
