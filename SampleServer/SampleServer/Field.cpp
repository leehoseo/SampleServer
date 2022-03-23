#include "Field.h"
#include "ScopeLock.h"

Field::Field(const FieldType& type, const int maxPlayer)
	: _type(type)
	, _maxPlayer(maxPlayer)
{
	static FieldKey::Type currentIndex = FieldKey::undefined;
	_key = ++currentIndex;
}

Field::~Field()
{

}

const FieldKey& Field::getKey() const
{
	return _key;
}

const FieldType& Field::getType() const
{
	return _type;
}

void Field::addPlayer(PlayerActor* player)
{
	ScopeLock lock(&_lock);
	_playerList.push_back(player);
}

void Field::removePlayer(PlayerActor* removePlayer)
{
	ScopeLock lock(&_lock);
	for (auto iter = _playerList.begin(); iter != _playerList.end(); ++iter)
	{
		PlayerActor* player = *iter;
		if (removePlayer->getActorKey() == player->getActorKey())
		{
			_playerList.erase(iter);
			return;
		}
	}
}

void Field::getPlayerList(std::vector<ActorKey>& outList)
{
	ScopeLock lock(&_lock);
	for (auto iter = _playerList.begin(); iter != _playerList.end(); ++iter)
	{
		PlayerActor* player = *iter;
		outList.push_back(player->getActorKey());
	}
}

const bool Field::isFull()
{
	ScopeLock lock(&_lock);
	return _maxPlayer <= _playerList.size();
}
