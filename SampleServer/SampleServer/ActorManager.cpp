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

	// ��Ÿ ������ �ܺο��� �Ѵ�.
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

void ActorManager::getPlayerSessionKey(const std::vector<ActorKey>& actorKeyList, std::vector<SessionKey>& outList)
{
	for (auto iter = actorKeyList.begin(); iter != actorKeyList.end(); ++iter)
	{
		SessionKey outKey;
		getPlayerSessionKey( *iter , outKey );

		if (true == outKey.isValid())
		{
			outList.push_back(outKey);
		}
	}
}

void ActorManager::getPlayerSessionKey(const ActorKey& actorKey, SessionKey& outKey)
{
	auto iter = _playerActorList.find(actorKey.get());
	if (iter == _playerActorList.end())
	{
		// �����äää�
		return;
	}

	PlayerActor* playerActor = iter->second;
	outKey = playerActor->getSessionKey();
}

Pool<PlayerActor>& ActorManager::getPlayerActorPool()
{
	if (false == _playerActorPool.isValid())
	{
		// ���� ó��
	}

	return _playerActorPool;
}
