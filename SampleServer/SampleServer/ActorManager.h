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

	void getActivePlayerActorSessionIds(std::vector<Session_ID>& sessionIdList);

private:
	Pool<PlayerActor>& getPlayerActorPool();
	Pool<PlayerActor> _playerActorPool;			// Pool�� ������� ���͵�

	std::unordered_map<ActorKey, PlayerActor*> _playerActorList;	// ���� ������� ���͵�
};
