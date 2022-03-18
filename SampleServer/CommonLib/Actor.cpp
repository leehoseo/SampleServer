#include "Actor.h"

Actor::Actor()
{
    static ActorKey currentActorKey = undefinedActorKey;
    _actorKey = ++currentActorKey;
}

Actor::~Actor()
{
}

void Actor::init()
{
}

void Actor::release()
{
}

void Actor::active()
{
}

void Actor::deactive()
{
}

Contents* Actor::getContents(const ContentsType& type)
{
    return _contentsList[type];
}

const ActorKey& Actor::getActorKey()
{
    return _actorKey;
}

void Actor::insertContents(Contents* contents)
{
    contents->init(this);
    _contentsList.insert(std::make_pair(contents->getType(), contents));
}
