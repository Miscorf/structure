#include <winsock2.h> //winsock2的头文件
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "UDASAPI.h"

using namespace std;

//勿忘，链接dll的lib
// #pragma comment(lib, "ws2_32.lib")

int main1()
{
    //生产环境
    // char *ip = "198.162.10.16";
    // int port = 24;

    //测试环境
    char *ip = "127.0.0.1";
    int port = 9000;
    // 创建udp控制
    UDP_control control = UDP_control(ip, port);
    SOCKET s = control.socket_id;
    Unpack unpack = Unpack(s);
    // clear and calculater pulse size
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

    Store_h5 store_h5 = Store_h5(s, file_name, dataset_name, point_num, dim, 10);
    store_h5.do_store(2);

    // HF5 myh5 = HF5(file_name, dataset_name, dim, 0);

    // time_t begin_time, after_time;
    // begin_time = time(NULL); //获取日历时间
    // int ret = 0;
    // do
    // {
    //     after_time = time(NULL);
    //     char buf[ep90_size * point_num] = {0};
    //     int recv_data_size = recv(s, buf, ep90_size * point_num, 0);
    //     char pulse_char[5];
    //     char *p = buf + 4;
    //     strncpy(pulse_char, p + 4, sizeof(pulse_char));
    //     cout << int(pulse_char[0]) << int(pulse_char[1]) << int(pulse_char[2]) << int(pulse_char[3]) << endl;
    //     char c[4] = {'E', 'B', '1', '1'};
    //     int pulse_id = strtol(c, nullptr, 16);
    //     cout << pulse_id << endl;
    //     for (size_t i = 0; i < 10; i++)
    //     {
    // printf("%x", buf[i]);
    // cout << endl;
    // }

    // cout << "pulse_id:" << pulse_id << endl;
    // now_tag = buf[7];
    // if (now_tag - last_tag != 1)
    //     cout << "error tag!" << int(now_tag) <<" "<< int(last_tag) << endl;
    // last_tag = now_tag;
    // herr_t status = myh5.extend_write_chunk(dim, buf);
    // ret++;
    // cout << int(buf[0]) << " " << int(buf[1]) << endl;

    // } while (ret < 5);

    // char bufw[100] = {0};·
    cout << "end";
    // cin >> bufw;
    // ret = send(s, bufw, 100, 0);

    return 0;
}