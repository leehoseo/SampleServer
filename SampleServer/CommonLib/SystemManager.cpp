#include "SystemManager.h"
#include "ThreadContents.h"

SystemManager::SystemManager()
{
}

SystemManager::~SystemManager()
{
}

void SystemManager::init(Actor* mainActor, Iocp* iocp)
{
    if ( nullptr != _mainActor || nullptr != _iocp )
    {
        return;
    }

    _mainActor = mainActor;
    _iocp = iocp;
}

Actor* SystemManager::getMainActor()
{
    return _mainActor;
}

Iocp* SystemManager::getIcop()
{
    return _iocp;
}

void SystemManager::insertAndRunThread()
{
    ThreadContents* threadContents = static_cast<ThreadContents*>(_mainActor->getContents(ContentsType::eThread));
    threadContents->insertAndRunThread();
}
