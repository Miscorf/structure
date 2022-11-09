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
    // HF5 hf5;
    int store_num; // 存储系数
    std::vector<char> v_buf;
    int buf_size = 0;
    char *bufp;

public:
    Store_h5(SOCKET id, int store_num, hsize_t dim[]);
    ~Store_h5();
    boolean recv_data(char *buf, int size);
    boolean write_hdf5(char *file, char *dataset, char *wdata);
    boolean write_hdf5(char *file, char *dataset, std::vector<das_data> wdata);
    // boolean do_store(int store_num, int sec);
    boolean do_store(char *file, char *dataset, int store_num, int sec);
};
#endif