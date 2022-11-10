#include <winsock2.h> //winsock2的头文件
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "UDASAPI.h"

using namespace std;

//勿忘，链接dll的lib
// #pragma comment(lib, "ws2_32.lib")

int main()
{
    // 生产环境
    char *ip = "192.168.10.16";
    int port = 24;

    // //测试环境
    // char *ip = "127.0.0.1";
    // int port = 9000;
    // 创建udp控制
    UDP_control control = UDP_control(ip, port);
    SOCKET s = control.socket_id;
    Unpack unpack = Unpack(s);
    // clear and  get pluse size
    if (unpack.clear())
    {
        cout << "clear right!" << endl;
    }
    else
    {
        cout << "clear error!" << endl;
    }
    int ep90_size = unpack.get_pluse_size();

    // write hdf5
    char file_name[20] = "my_test_file.h5";
    char dataset_name[20] = "my_test_dataset";
    int point_num = 1; // 存储系数
    // chunk dim
    hsize_t dim[2] = {1 * point_num, ep90_size};

    Store store = Store(s, point_num, dim);
    store.do_store(file_name, dataset_name, 2, 5);

    cout << "end";
    return 0;
}