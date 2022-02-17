#pragma once
#include "TrId.h"

enum class ThreadType
{
	eAi = 0,	// 서버에서 주로 통신하는 ThreadType
	eAction,	// 이동, 공격등 빠른 응답성을 필요로 하는 ThreadType
	eContents,	// 아이템 획득, 판매 등 응답성이 빠르지 않아도 되는 ThreadType
	eClient,	// 클라이언트용 ThreadType을 나눌 필요는 없다
	eCount,
};


class Tr
{
public:
	Tr();
	Tr( const TrId trId, const ThreadType threadType, const int maxSize );
	~Tr();

public:
	TrId		_trId;		// 어느 쓰래드에서 돌릴지
	ThreadType	_threadType;		// 어느 쓰래드에서 돌릴지
	int			_maxSize;		// 클래스의 최대 크기 검증용
};