#include "CharacterActor.h"


CharacterActor::CharacterActor()
	: Actor()
{

}

CharacterActor::~CharacterActor()
{

}

const std::string& CharacterActor::getName()
{
	return _name;
}

void CharacterActor::setName(const std::string& name)
{
	_name = name;
}

void CharacterActor::init()
{
	__super::init();
}

void CharacterActor::release()
{
	__super::release();
	_name.clear();
}

void CharacterActor::active()
{
	__super::active();
}

void CharacterActor::deactive()
{
	__super::deactive();
}
