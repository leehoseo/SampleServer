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
	// Ŭ���̾�Ʈ�� clientActor, ������ serverActor�� �Ҵ�ɰŴ�.
	Actor* _mainActor = nullptr; 
	Iocp* _iocp = nullptr;
};

