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

	_playerActorList.insert(std::make_pair(newPlayerActor->getActorKey().get(), newPlayerActor));

	// 기타 세팅은 외부에서 한다.
	return newPlayerActor;
}

void ActorManager::deletePlayerActor(const ActorKey& actorKey)
{
	auto iter = _playerActorList.find(actorKey.get());
	if (_playerActorList.end() == iter)
	{
		return;
	}

	PlayerActor* deletedPlayerActor = iter->second;

	_playerActorPool.push(deletedPlayerActor);
	_playerActorList.erase(actorKey.get());
}

void ActorManager::deletePlayerActor(const SessionKey& sessionKey)
{
	for (auto iter = _playerActorList.begin(); iter != _playerActorList.end(); ++iter)
	{
		PlayerActor* deletedPlayerActor = iter->second;
		if (deletedPlayerActor->getSessionKey() == sessionKey)
		{
			_playerActorPool.push(deletedPlayerActor);
			_playerActorList.erase(iter);

			return;
		}
	}
}

void ActorManager::getActivePlayerActorSessionIds(std::vector<SessionKey>& sessionKeyList)
{
	for (auto iter = _playerActorList.begin(); iter != _playerActorList.end(); ++iter)
	{
		PlayerActor* playerActor = iter->second;
		sessionKeyList.push_back(playerActor->getSessionKey());
	}
}

Pool<PlayerActor>& ActorManager::getPlayerActorPool()
{
	if (false == _playerActorPool.isValid())
	{
		// 에러 처리
	}

	return _playerActorPool;
}
