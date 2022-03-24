#include "ServerFieldContents.h"
#include "FieldManager.h"
#include "TrField.h"
#include "SystemManager.h"
#include "ServerNetworkContents.h"
#include "ActorManager.h"
ServerFieldContents::ServerFieldContents()
{
}

ServerFieldContents::~ServerFieldContents()
{
}

void ServerFieldContents::responseTrLoginToLobbyReq(TrLoginToLobbyReq* req)
{
	PlayerActor* loginedPlayer = static_cast<PlayerActor*>(_owner);
	loginedPlayer->setName(req->_name);

	Field* field = FieldManager::getInstance()->getAccessibleField(FieldType::eLobby);

	_currentFieldKey = field->getKey();
	field->addPlayer(loginedPlayer);

	std::vector<PlayerActor*> playerList;
	field->getPlayerList(playerList);

	Actor* serverActor = SystemManager::getInstance()->getMainActor();
	ServerNetworkContents* networkContents = static_cast<ServerNetworkContents*>(serverActor->getContents(ContentsType::eNetwork));

	const int size = playerList.size();
	for (int index = 0 ; index < size ; ++index )
	{
		PlayerActor* player = playerList[index];

		if (loginedPlayer->getActorKey() != player->getActorKey())
		{
			TrLoginToLobbyAck* ack = new TrLoginToLobbyAck();
			ack->set(player->getActorKey(), player->getName().c_str());
			networkContents->sendToActor(ack, 0, loginedPlayer->getActorKey());
		}

		TrLoginToLobbyAck * ack = new TrLoginToLobbyAck();
		ack->set(loginedPlayer->getActorKey(), loginedPlayer->getName().c_str());
		networkContents->sendToActor(ack, 0, player->getActorKey());
	}
}
