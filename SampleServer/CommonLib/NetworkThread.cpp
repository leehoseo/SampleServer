#include "NetworkThread.h"
#include "SystemManager.h"
#include "Iocp.h"

NetworkThread::NetworkThread()
	: Thread(ThreadType::eNetwork)
{
}

NetworkThread::~NetworkThread()
{
}

bool NetworkThread::work()
{
	Iocp* iocp = SystemManager::getInstance()->getIcop();

	iocp->execute();

	// �ݺ� ����
	return true;
}

bool NetworkThread::checkWaitExitCondition()
{
	// ���� ���� �����Ŵ� ���߿� ������ �þ�� 1ms�� �ѹ��������� ����
	return true;
}
