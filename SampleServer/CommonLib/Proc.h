#pragma once
#include "TrId.h"
#include "Singleton.h"
#include <unordered_map>

#define MAKE_PROC(trId)																		\
class trId##Proc : public Proc																\
{																							\
public:																						\
	trId##Proc() : Proc() { ProcManager::getInstance()->insertProc(TrId::##trId , this); }	\
	virtual ~trId##Proc() {}																\
																							\
public:																						\
	void process(Tr* tr);																	\
};																							\

#define MAKE_PROCESS(trId)				\
trId##Proc trId##Instance;				\
void trId##Proc::process(Tr* tr)		\

class Tr;
class Proc
{
public:
	Proc() {};
	virtual ~Proc() {};
	virtual void process(Tr* tr) = 0;
};

class ProcManager : public Singleton<ProcManager>
{
public:
	ProcManager() {};
	virtual ~ProcManager() {};

	void insertProc(TrId id, Proc* proc);
	Proc* getProc(TrId id);
private:
	std::unordered_map<TrId, Proc*> _procList;
};