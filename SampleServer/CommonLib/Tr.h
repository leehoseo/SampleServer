#pragma once
#include "TrId.h"
#include "Thread.h"
#include "Base.h"
#include "BaseTime.h"
#include <vector>

class Tr
{
public:
	Tr();
	Tr( const TrId trId, const ThreadType type, const int maxSize );
	~Tr();

public:
	void send(Tr* tr, const TickCount64 timer, const SessionKey& sessionKey);

	TrId		_trId;		// ��� �����忡�� ������
	ThreadType	_type;		// ��� �����忡�� ������
	int			_maxSize;		// Ŭ������ �ִ� ũ�� ������
};