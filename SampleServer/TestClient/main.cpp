#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <stdio.h>
#include <MSWSock.h>
#include <vector>
#include "Iocp.h"
#include "Socket.h"

#pragma comment(lib, "ws2_32.lib")

LPFN_CONNECTEX g_connect;
HANDLE ioHandle;
SOCKET hSocket;
WSABUF wsabuf;
WSABUF sendWsabuf;

WSAOVERLAPPED overlapped;
unsigned int __stdcall WorkThread(LPVOID pComPort);

void ConnectEx(SOCKET& socket, GUID guid) 
{
    DWORD dwbyte{ 0 };
    WSAIoctl(socket, SIO_GET_EXTENSION_FUNCTION_POINTER,
        &guid, sizeof(guid),
        &g_connect, sizeof(g_connect),
        &dwbyte, NULL, NULL);
}

int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        //ErrorHandling("WSAStartup() error!");
    }

    ioHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);


    hSocket = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (hSocket == INVALID_SOCKET)
    {
        //ErrorHandling("WSAStartup() error!");
    }

    SOCKADDR_IN recvAddr;
    memset(&recvAddr, 0, sizeof(recvAddr));
    recvAddr.sin_family = AF_INET;
    //recvAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    recvAddr.sin_port = htons(5555);
    inet_pton(AF_INET, "127.0.0.1", &recvAddr.sin_addr.s_addr);

    //bind(hSocket, reinterpret_cast<sockaddr*>(&recvAddr), sizeof(recvAddr));

   // ConnectEx(hSocket, WSAID_CONNECTEX);
    //if (connect(hSocket, (SOCKADDR*)&recvAddr, sizeof(recvAddr)) == SOCKET_ERROR)
    //{
    //    //ErrorHandling("WSAStartup() error!");
    //}

    memset(&overlapped, 0, sizeof(overlapped));

    if (connect(hSocket, (SOCKADDR*)&recvAddr, sizeof(recvAddr)) == SOCKET_ERROR)
    {
        //ErrorHandling("WSAStartup() error!");
    }

    //g_connect(hSocket, reinterpret_cast<SOCKADDR*>(&recvAddr), sizeof(recvAddr), NULL, NULL, NULL,
    //            reinterpret_cast<LPOVERLAPPED>(&overlapped));

    WSAOVERLAPPED recvOverlapped;
    ZeroMemory(&recvOverlapped, sizeof(recvOverlapped));
    DWORD flag{ 0 };

    char initStr[1024] = {};

    sendWsabuf.buf = initStr;
    sendWsabuf.len = 1204;
    WSARecv(hSocket, &wsabuf, 1, NULL, &flag, &recvOverlapped, 0);

    CreateIoCompletionPort(reinterpret_cast<HANDLE>(hSocket),ioHandle, 1, 0);

    SYSTEM_INFO SystemInfo;
    GetSystemInfo(&SystemInfo);
    for (int i = 0; i < 1; ++i)
        _beginthreadex(NULL, 0, WorkThread, (LPVOID)ioHandle, 0, NULL);

   
    char str[1204] = {};
    while (true)
    {
        std::cin >> str;

        OVER_EX* over_ex = new OVER_EX;
        char s[1204];
        ZeroMemory(&over_ex->over_, sizeof(over_ex->over_));

        over_ex->wsabuf_.len = 1204;
        over_ex->wsabuf_.buf = over_ex->buffer_;
        memcpy(over_ex->buffer_, &str, 1204);

        WSASend(hSocket, &over_ex->wsabuf_,1, 0, 0, &over_ex->over_, NULL);
    }

    closesocket(hSocket);

    WSACleanup();

    return 0;
}

unsigned int __stdcall WorkThread(LPVOID pComPort)
{
    DWORD		io_byte;
    DWORD	id;

    char initStr[1024] = {};

    while (true) 
    {
        IocpEvents readEvents;

        const bool result = GetQueuedCompletionStatusEx(ioHandle, readEvents.m_events, Iocp::MAX_EVENT_COUNT, (ULONG*)&readEvents.m_eventCount, 0, FALSE);
        if (false == result)
        {
            continue;

        }

        // 받은 이벤트 각각을 처리합니다.
        for (int index = 0; index < readEvents.m_eventCount; ++index)
        {
            OVERLAPPED_ENTRY& readEvent = readEvents.m_events[index];

            if (0 == wsabuf.len)
            {
                continue;
            }

            std::cout << "Server Recv : " << wsabuf.buf << std::endl;

            wsabuf.buf = initStr;
            wsabuf.len = 1204;

            DWORD flag{ 0 };
            WSARecv(hSocket, &wsabuf, 1, NULL, &flag, &overlapped, 0);
        }
    }

    return 0;
}