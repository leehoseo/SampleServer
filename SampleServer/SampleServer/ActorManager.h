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
	//void deletePlayerActorByActorKey(const ActorKey& actorKey);
	void deletePlayerActor(const Session_ID& sessionId);

	void getActivePlayerActorSessionIds(std::vector<Session_ID>& sessionIdList);

private:
	Pool<PlayerActor>& getPlayerActorPool();
	Pool<PlayerActor> _playerActorPool;			// Pool에 대기중인 엑터들

	std::unordered_map<ActorKey, PlayerActor*> _playerActorList;	// 실제 사용중인 엑터들
};

