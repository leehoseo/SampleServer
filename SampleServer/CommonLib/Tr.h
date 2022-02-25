#pragma once
#include "TrId.h"
#include "Thread.h"

class Tr
{
public:
	Tr();
	Tr( const TrId trId, const ThreadType type, const int maxSize );
	~Tr();

public:
	TrId		_trId;		// ��� �����忡�� ������
	ThreadType	_type;		// ��� �����忡�� ������
	int			_maxSize;		// Ŭ������ �ִ� ũ�� ������
};