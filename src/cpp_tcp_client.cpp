#include <winsock2.h> //winsock2的头文件
#include <iostream>
#include <stdint.h>
#include <hdf5.h>
#include <H5Cpp.h>
#include "../include/utils.h"
#include "../src/class/HF5.cpp"
#include "time.h"

using namespace std;

//勿忘，链接dll的lib
#pragma comment(lib, "ws2_32.lib")

int main()
{
    //加载winsock2的环境
    WSADATA wd;
    if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
    {
        cout << "WSAStartup  error:" << GetLastError() << endl;
        return 0;
    }

    // 1.创建流式套接字
    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
    {
        cout << "socket  error:" << GetLastError() << endl;
        return 0;
    }

    // 2.链接服务器
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9000);
    //  addr.sin_addr.s_addr = inet_addr("192.168.10.16");
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int len = sizeof(sockaddr_in);
    if (connect(s, (SOCKADDR *)&addr, len) == SOCKET_ERROR)
    {
        cout << "connect  error:" << GetLastError() << endl;
        return 0;
    }
    else
    {
        cout << "connet right!" << endl;
    }

    // 3接收服务端的消息

    // 获取两个ep90之间的间隔 ep90_size
    int pack_max_size = 500;
    char find_size_buf[pack_max_size] = {0};
    int recv_data_size = recv(s, find_size_buf, pack_max_size, 0);
    int ep90_size = EP90_size(find_size_buf, pack_max_size);

    //按ep90_size读取每个脉冲
    //读取第一个ep90位置，并对第二个脉冲丢弃该位置前的缓冲
    char find_flag_buf[ep90_size] = {0};
    recv_data_size = recv(s, find_flag_buf, ep90_size, 0);
    int flag = findEB90_0000(find_flag_buf, ep90_size);

    // 丢弃flag之前的buf
    char drop_buf[flag] = {0};
    recv_data_size = recv(s, drop_buf, flag, 0);

    // 查看下一个buf是否EB90开头
    char check_buf[ep90_size];
    recv_data_size = recv(s, check_buf, ep90_size, 0);
    cout << "check:";
    cout << int(check_buf[0]) << " " << int(check_buf[1]) << endl;
    int ret = 0;
    cout << "epch_size:" << ep90_size << endl;

    // write hdf5
    char file_name[20] = "my_test_file.h5";
    char dataset_name[20] = "my_test_dataset";
    hsize_t dim[2] = {1, ep90_size};
    // int data[1][3] = {{1, 1, 3}};
    HF5 myh5 = HF5(file_name, dataset_name, dim, 0);
    // hsize_t buf[2];
    // myh5.get_dims(buf);
    // cout << "buf:" << buf[0] << " " << buf[1] << endl;
    time_t begin_time, after_time;
    begin_time = time(NULL); //获取日历时间

    do
    {
        after_time = time(NULL);
        char buf[ep90_size] = {0};
        int recv_data_size = recv(s, buf, ep90_size, 0);

        herr_t status = myh5.extend_write_chunk(dim, buf);
        ret++;
        cout << int(check_buf[0]) << " " << int(check_buf[1]) << endl;

    } while (after_time - begin_time < 5);

    // 3 随时给服务端发消息

    // char bufw[100] = {0};
    cout << "输入任意字符结束。";
    // cin >> bufw;
    // ret = send(s, bufw, 100, 0);
    // 4.关闭监听套接字
    closesocket(s);

    // 清理winsock2的环境
    WSACleanup();

    return 0;
}