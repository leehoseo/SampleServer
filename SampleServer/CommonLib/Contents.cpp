#include "Contents.h"
#include "Actor.h"

Contents::Contents()
{
}

Contents::~Contents()
{
}

Actor* Contents::getOwner()
{
	return _owner;
}

void Contents::init(Actor* owner)
{
	_owner = owner;
}

void Contents::active()
{

}

void Contents::deactive()
{
	_owner = nullptr;
}

bool Contents::isValid()
{
	return nullptr != _owner;
}
