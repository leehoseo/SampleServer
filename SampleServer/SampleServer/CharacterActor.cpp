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
