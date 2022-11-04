#ifndef _STORE_H5
#define _STORE_H5

#include "HF5.h"
#include <winsock2.h>
#include <vector>
#include <iostream>

class Store_h5
{
private:
    SOCKET socket_id;
    hsize_t dim[2];
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