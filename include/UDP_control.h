#ifndef HF5_FILE
#define HF5_FILE

#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>

class UDP_control
{
private:
    sockaddr_in remote_address; // 远程地址
    int remote_address_len;     // 远程地址长度
    WSADATA wd;
    // socket环境
    WSADATA wsaData;

public:
    SOCKET socket_id; // 标识
    UDP_control(char ip[], int port);

public:
    ~UDP_control();
};
#endif
