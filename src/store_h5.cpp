#include "Store_h5.h"

Store_h5::Store_h5(SOCKET id, char *file, char *dataset, int store_num, hsize_t _dim[], int time)
{

    dim[0] = _dim[0];
    dim[1] = _dim[1];
    hf5 = HF5(file, dataset, _dim, time);
    socket_id = id;
}
Store_h5::~Store_h5()
{
}
boolean Store_h5::do_store(int store_num)
{

    int size = store_num * dim[1];
    char temp_data[size];

    // unpack(buf);
    int ret = 0;
    while (ret < 10)
    {
        recv_data(temp_data, size);
        std::cout << "temp:" << int(temp_data[0]) << int(temp_data[1]) << std::endl;
        wtite_hdf5(temp_data);
        ret++;
    }
    hf5.close();
}
boolean Store_h5::recv_data(char *buf, int size)
{
    int c = recv(socket_id, buf, size, 0);
}

boolean Store_h5::wtite_hdf5(char *wdata)
{
    return hf5.extend_write_chunk(dim, wdata);
}