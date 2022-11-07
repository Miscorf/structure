#include "Store_h5.h"

Store_h5::Store_h5(SOCKET id, char *file, char *dataset, int store_num, hsize_t _dim[], int time)
{
    pluse_size = _dim[1];
    dim[0] = _dim[0];
    dim[1] = _dim[1] - 20 - 4; // 20 开头 4 结尾
    hf5 = HF5(file, dataset, dim, time);
    socket_id = id;
}
Store_h5::~Store_h5()
{
}
boolean Store_h5::do_store(int store_num)
{

    int recv_size = store_num * pluse_size;
    char temp_data[recv_size];

    time_t begin_time, after_time;
    begin_time = time(NULL); //获取日历时间
    // unpack(buf);
    int ret = 0;
    do
    {
        after_time = time(NULL);
        recv_data(temp_data, recv_size);
        std::vector<das_data> data_buf;
        for (size_t i = 0; i < store_num; i++)
        {
            das_data data = das_data(temp_data + i * pluse_size, pluse_size);
            data_buf.push_back(data);
        }
        // std::cout << "temp:" << int(temp_data[0]) << int(temp_data[1]) << std::endl;
        for (size_t i = 0; i < store_num; i++)
        {
            wtite_hdf5(&temp_data[20 + pluse_size * i]);
        }

        ret++;
    } while (after_time - begin_time < 3);

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