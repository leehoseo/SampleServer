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

//void ActorManager::deletePlayerActor(const ActorKey& actorKey)
//{
//	auto iter = _playerActorList.find(actorKey);
//	if (_playerActorList.end() == iter)
//	{
//		return;
//	}
//
//	PlayerActor* deletedPlayerActor = iter->second;
//
//	_playerActorPool.push(deletedPlayerActor);
//	_playerActorList.erase(actorKey);
//}

void ActorManager::deletePlayerActor(const Session_ID& sessionId)
{
	for (auto iter = _playerActorList.begin(); iter != _playerActorList.end(); ++iter)
	{
		PlayerActor* deletedPlayerActor = iter->second;
		if (deletedPlayerActor->getSessionId() == sessionId)
		{
			_playerActorPool.push(deletedPlayerActor);
			_playerActorList.erase(iter);

			return;
		}
	}
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
		// 에러 처리
	}

	return _playerActorPool;
}
