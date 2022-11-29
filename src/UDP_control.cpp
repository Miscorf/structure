#include "UDP_control.h"
#include <WS2tcpip.h>
#include <winsock2.h>
#include <iostream>
using namespace std;

UDP_control::UDP_control(char ip[], int port, int tag)
{

    //加载winsock2的环境
    if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
    {
        cout << "WSAStartup  error:" << GetLastError() << endl;
    }
    // tag == 1 创建tcp socket
    if (tag == 1)
    {
        socket_id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    }
    else if (tag == 2)
    {
        // 创建udp socket
        socket_id = socket(AF_INET, SOCK_DGRAM, 0);
    }

    if (socket_id == INVALID_SOCKET)
    {
        cout << "socket  error:" << GetLastError() << endl;
    }
    remote_address.sin_family = AF_INET;
    remote_address.sin_port = htons(port);
    remote_address.sin_addr.s_addr = inet_addr(ip);
    int len = sizeof(sockaddr_in);
    // if (connect(socket_id, (SOCKADDR *)&remote_address, len) == SOCKET_ERROR)
    // {
    //     cout << "connect  error:" << GetLastError() << endl;
    // }
    // else
    // {
    //     cout << "connet right!" << endl;
    // }
}
UDP_control::~UDP_control()
{
    // 4.关闭监听套接字
    closesocket(socket_id);

    // 清理winsock2的环境
    WSACleanup();
}

int UDP_control::start_collect()
{
    int len = sizeof(SOCKADDR);
    // 开始采集命令 fffe000301
    uint8_t buf[9] = {0xff, 0x80, 0x00, 0x01, 0xff, 0xfe, 0x00, 0x03, 0x01};
    int flag = sendto(socket_id, (char *)&buf, sizeof(buf), 0, (SOCKADDR *)&remote_address, len);
    return flag;
}
int UDP_control::end_collect()
{
    int len = sizeof(SOCKADDR);
    // 停止采集命令 fffe00030f
    uint8_t buf[9] = {0xff, 0x80, 0x00, 0x01, 0xff, 0xfe, 0x00, 0x03, 0x0F};
    int flag = sendto(socket_id, (char *)&buf, sizeof(buf), 0, (SOCKADDR *)&remote_address, len);
    return flag;
}

struct data
{
    uint8_t head[4] = {0xeb, 0x90, 0x00, 0x00};
    long pluse_id;
    long data[100];
};
int UDP_control::tcp_send()
{
    bind(socket_id, (sockaddr *)&remote_address, sizeof(remote_address));
    listen(socket_id, 20);
    sockaddr client_addr;
    int nclient_addr = sizeof(client_addr);
    cout << "wait for client" << endl;
    SOCKET client_socket = accept(socket_id, &client_addr, &nclient_addr);
    cout << "client connect right" << endl;

    long n = 0;
    while (1)
    {
        char *send_buf;
        data d;
        d.pluse_id = n++;
        int buf_size = sizeof(d);
        send(client_socket, (char *)&d, buf_size, NULL);
    }
}
