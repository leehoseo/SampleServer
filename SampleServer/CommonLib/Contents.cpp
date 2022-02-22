#include "Contents.h"
#include "Actor.h"


Contents::Contents()
{
}

Contents::~Contents()
{
}

void Contents::init(Actor* owner)
{
	_owner = owner;
}

Actor* Contents::getOwner()
{
	return _owner;
}

bool Contents::isValid()
{
	return nullptr != _owner;
}
