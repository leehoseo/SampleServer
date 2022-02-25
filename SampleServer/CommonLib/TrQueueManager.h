#pragma once
#include "Singleton.h"
#include "Lock.h"
#include "Tr.h"
#include <queue>
#include "Thread.h"
class TrQueueManager : public Singleton< TrQueueManager>
{
public:
	TrQueueManager();
	~TrQueueManager();

public:
	void push(Tr* tr);
	Tr* pop( const ThreadType& type);
	bool isExist( const ThreadType& type);


private:
	Lock _aiLock;
	std::queue<Tr*> _aiTrList;

	Lock _actionLock;
	std::queue<Tr*> _actionTrList;

	Lock _contentsLock;
	std::queue<Tr*> _contentsTrList;
};

