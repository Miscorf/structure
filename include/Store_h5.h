#ifndef _STORE_H5
#define _STORE_H5

#include <winsock2.h>
#include <vector>
#include <iostream>
#include "das_data.h"
#include "HF5.h"

class Store_h5
{
private:
    SOCKET socket_id;
    int pluse_size; // 每个脉冲大小 也就是tcp 报文大小
    hsize_t dim[2]; // 存储的维度 dim[1]为数据大小
    HF5 hf5;
    char *buf;
    std::vector<char> v_buf;

public:
    Store_h5(SOCKET id, char *file, char *dataset, int store_num, hsize_t dim[], int time);
    ~Store_h5();
    boolean recv_data(char *buf, int size);
    boolean wtite_hdf5(char *wdata);
    boolean do_store(int store_num);
};

#endif