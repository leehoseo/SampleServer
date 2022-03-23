#pragma once
#include "Base.h"
#include "PlayerActor.h"
#include "Lock.h"
#include <vector>

enum class FieldType
{
	eLobby = 0,
	eInGame,
	eCount,
};

class Field
{
public:
	Field(const FieldType& type , const int maxPlayer);
	virtual ~Field();

	const FieldKey& getKey() const;
	const FieldType& getType() const;

	void addPlayer(PlayerActor* player);
	void removePlayer(PlayerActor* player);
	void getPlayerList(std::vector<ActorKey>& outList);

	const bool isFull();

private:
	int _maxPlayer = 0;

	FieldKey _key;
	FieldType _type = FieldType::eCount;

	Lock _lock;
	std::vector<PlayerActor*> _playerList;

	// ���⼭ NPC, ���� ����� �� �����ҰŴ� ����� Ŀ���� ���� �����.
};

