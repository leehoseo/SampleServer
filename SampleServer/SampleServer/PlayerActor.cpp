#include "PlayerActor.h"

PlayerActor::PlayerActor()
	:CharacterActor()
{
}

PlayerActor::~PlayerActor()
{
}

const Session_ID& PlayerActor::getSessionId()
{
	return _sessionId;
}

void PlayerActor::setSessionId(const Session_ID& sessionId)
{
	_sessionId = sessionId;
}

void PlayerActor::init()
{
}

void PlayerActor::release()
{
}

void PlayerActor::active()
{
}

void PlayerActor::deactive()
{
}
