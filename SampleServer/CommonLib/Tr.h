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
	TrId		_trId;		// 어느 쓰래드에서 돌릴지
	ThreadType	_type;		// 어느 쓰래드에서 돌릴지
	int			_maxSize;		// 클래스의 최대 크기 검증용
};