#include "DispatcherThread.h"
#include "Dispatcher.h"

DispatcherThread::DispatcherThread()
	: Thread(ThreadType::eDispatcher)
{
}

DispatcherThread::~DispatcherThread()
{
}

bool DispatcherThread::work()
{
	Dispatcher::getInstance()->execute();

	// �ݺ� ����
	return true;
}

bool DispatcherThread::checkWaitExitCondition()
{
	// ���� ���� �����Ŵ� ���߿� ������ �þ�� 1ms�� �ѹ��������� ����
	return true;
}
