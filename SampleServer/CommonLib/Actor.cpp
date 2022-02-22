#include "Actor.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

Contents* Actor::getContents(const ContentsType& type)
{
    return _contentsList[type];
}

void Actor::insertContents(Contents* contents)
{
    contents->init(this);
    _contentsList.insert(std::make_pair(contents->getType(), contents));
}
