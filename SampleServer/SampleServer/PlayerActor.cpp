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
	__super::init();
}

void PlayerActor::release()
{
	__super::release();
	_sessionId = undefinedSessionId;
}

void PlayerActor::active()
{
	__super::active();
}

void PlayerActor::deactive()
{
	__super::deactive();
}
