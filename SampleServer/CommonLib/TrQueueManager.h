#pragma once
#include "Singleton.h"
#include "Lock.h"
#include "Tr.h"
#include <queue>

class TrQueueManager : public Singleton< TrQueueManager>
{
public:
	TrQueueManager();
	~TrQueueManager();

public:
	void push(Tr* tr);
	void pop( const TrType& type, Tr* outTr);

private:
	Lock _aiLock;
	std::queue<Tr*> _aiTrList;

	Lock _actionLock;
	std::queue<Tr*> _actionTrList;

	Lock _contentsLock;
	std::queue<Tr*> _contentsTrList;

	Lock _clientLock;
	std::queue<Tr*> _clientTrList;
};

