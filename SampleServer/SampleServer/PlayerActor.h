#pragma once
#include "CharacterActor.h"
#include "Base.h"
#include <string>

class PlayerActor : public CharacterActor
{
public:
	PlayerActor();
	virtual ~PlayerActor();

	const Session_ID& getSessionId();
	void			  setSessionId(const Session_ID& sessionId);


public:
	// ������ �ʱ�ȭ �Ǵ� �����ö�
	void init();

	// �ı��ɶ�
	void release();

	// pop
	void active();

	// push
	void deactive();


private:
	Session_ID _sessionId = undefinedSessionId;
};

