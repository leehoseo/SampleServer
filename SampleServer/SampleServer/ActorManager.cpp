#include "ActorManager.h"

ActorManager::ActorManager()
{
	const int playerActorPoolSize = 4;

	{
		_playerActorPool.init(playerActorPoolSize);
	}
}

ActorManager::~ActorManager()
{
}

PlayerActor* ActorManager::createPlayerActor()
{
	PlayerActor* newPlayerActor = _playerActorPool.pop();

	_playerActorList.insert(std::make_pair(newPlayerActor->getActorKey(), newPlayerActor));

	// ��Ÿ ������ �ܺο��� �Ѵ�.
	return newPlayerActor;
}

void ActorManager::deletePlayerActor(const ActorKey& actorKey)
{
	PlayerActor* deletedPlayerActor = _playerActorList.find(actorKey)->second;

	_playerActorPool.push(deletedPlayerActor);
}

void ActorManager::getActivePlayerActorSessionIds(std::vector<Session_ID>& sessionIdList)
{
	for (auto iter = _playerActorList.begin(); iter != _playerActorList.end(); ++iter)
	{
		PlayerActor* playerActor = iter->second;
		sessionIdList.push_back(playerActor->getSessionId());
	}
}

Pool<PlayerActor>& ActorManager::getPlayerActorPool()
{
	if (false == _playerActorPool.isValid())
	{
		// ���� ó��
	}

	return _playerActorPool;
}
