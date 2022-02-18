#pragma once
#include "TrId.h"
#include <unordered_map>

class Tr;
class Proc
{
public:
	static std::unordered_map<TrId, Proc*> _procList;
	static void insertProcList(TrId id, Proc* proc)
	{
		Proc::_procList.insert(std::make_pair(id, proc));
	}

public:
	Proc();
	~Proc() {};

public:
	virtual void process(Tr* tr) = 0;
};

static void insertProcList(TrId id, Proc* proc)
{
	Proc::_procList.insert(std::make_pair(id, proc));
}

#define MAKE_PROC(trId)								\
class trId##Proc : public Proc						\
{													\
public:												\
	trId##Proc() : Proc() {}				\
	virtual ~trId##Proc() {}						\
													\
public:												\
	virtual void process(Tr* tr);					\
};													\
													\
insertProcList( TrId::trId, new trId##Proc()  );	\

/*Ŭ�� �۾��� ��� �� �� ���� �ϳ��� Proc���� �� ������ �Ẹ��*/
/*Proc* clone() { return new trId##Proc(); };*/