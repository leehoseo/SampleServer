#include "PlayerActor.h"
#include "ServerFieldContents.h"

PlayerActor::PlayerActor()
	:CharacterActor()
{
#define MAKE_CONTENTS(Contents) { Contents* contents = new Server##Contents(); insertContents(contents); };

	// NetworkContents
	MAKE_CONTENTS(FieldContents);
}

PlayerActor::~PlayerActor()
{
}

const SessionKey& PlayerActor::getSessionKey()
{
	return _sessionKey;
}

void PlayerActor::setSessionKey(const SessionKey& sessionKey)
{
	_sessionKey = sessionKey;
}

void PlayerActor::init()
{
	__super::init();
}

void PlayerActor::release()
{
	_sessionKey.clear();

	__super::release();
}

void PlayerActor::active()
{
	__super::active();
}

void PlayerActor::deactive()
{
	__super::deactive();
}
