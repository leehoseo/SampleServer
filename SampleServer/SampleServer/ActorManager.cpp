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

	// 기타 세팅은 외부에서 한다.
	return newPlayerActor;
}

void ActorManager::deletePlayerActor(const ActorKey& actorKey)
{
	PlayerActor* deletedPlayerActor = _playerActorList.find(actorKey)->second;

	_playerActorPool.push(deletedPlayerActor);
}

Pool<PlayerActor>& ActorManager::getPlayerActorPool()
{
	if (false == _playerActorPool.isValid())
	{
		// 에러 처리
	}

	return _playerActorPool;
}
