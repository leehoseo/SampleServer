#pragma once
#include "TrId.h"

enum class ThreadType
{
	eAi = 0,	// �������� �ַ� ����ϴ� ThreadType
	eAction,	// �̵�, ���ݵ� ���� ���伺�� �ʿ�� �ϴ� ThreadType
	eContents,	// ������ ȹ��, �Ǹ� �� ���伺�� ������ �ʾƵ� �Ǵ� ThreadType
	eClient,	// Ŭ���̾�Ʈ�� ThreadType�� ���� �ʿ�� ����
	eCount,
};


class Tr
{
public:
	Tr();
	Tr( const TrId trId, const ThreadType threadType, const int maxSize );
	~Tr();

public:
	TrId		_trId;		// ��� �����忡�� ������
	ThreadType	_threadType;		// ��� �����忡�� ������
	int			_maxSize;		// Ŭ������ �ִ� ũ�� ������
};