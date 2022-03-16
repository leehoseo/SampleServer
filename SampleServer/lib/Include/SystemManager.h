#pragma once
#include "Singleton.h"
#include "Actor.h"
#include "Iocp.h"

class SystemManager : public Singleton<SystemManager>
{
public:
	SystemManager();
	~SystemManager();
		
public:
	void init(Actor* mainActor, Iocp* iocp );
	Actor* getMainActor();
	Iocp* getIcop();

	void insertAndRunThread();

private:
	// 클라이언트는 clientActor, 서버는 serverActor가 할당될거다.
	Actor* _mainActor = nullptr; 
	Iocp* _iocp = nullptr;
};

