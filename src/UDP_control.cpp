#include "UDP_control.h"
#include <WS2tcpip.h>
#include <winsock2.h>
#include <iostream>
using namespace std;

UDP_control::UDP_control(char ip[], int port)
{

    //加载winsock2的环境
    if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
    {
        cout << "WSAStartup  error:" << GetLastError() << endl;
    }
    socket_id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_id == INVALID_SOCKET)
    {
        cout << "socket  error:" << GetLastError() << endl;
    }
    remote_address.sin_family = AF_INET;
    remote_address.sin_port = htons(port);
    remote_address.sin_addr.s_addr = inet_addr(ip);
    int len = sizeof(sockaddr_in);
    if (connect(socket_id, (SOCKADDR *)&remote_address, len) == SOCKET_ERROR)
    {
        cout << "connect  error:" << GetLastError() << endl;
    }
    else
    {
        cout << "connet right!" << endl;
    }
}

UDP_control::~UDP_control()
{
    // 4.关闭监听套接字
    closesocket(socket_id);

    // 清理winsock2的环境
    WSACleanup();
}
