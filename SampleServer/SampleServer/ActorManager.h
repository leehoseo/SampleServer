#pragma once
#include "Singleton.h"
#include "Pool.hpp"
#include "PlayerActor.h"
#include <unordered_map>

class ActorManager : public Singleton<ActorManager>
{
public:
	ActorManager();
	virtual ~ActorManager();

	PlayerActor* createPlayerActor();
	void deletePlayerActor(const ActorKey& actorKey);
	void deletePlayerActor(const SessionKey& sessionKey);

	void getActivePlayerActorSessionIds(std::vector<SessionKey>& sessionKeyList);

private:
	Pool<PlayerActor>& getPlayerActorPool();
	Pool<PlayerActor> _playerActorPool;			// Pool에 대기중인 엑터들

	std::unordered_map<ActorKey::Type, PlayerActor*> _playerActorList;	// 실제 사용중인 엑터들
};

