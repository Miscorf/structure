#include <pthread.h>
#include "Store.h"
#include "assert.h"
#define GB 1024 * 1024 * 1024
Store::Store(SOCKET id, int store_num, hsize_t _dim[])
{
    pluse_size = _dim[1];
    dim[0] = _dim[0];
    dim[1] = _dim[1] - 20 - 4; // 20 开头 4 结尾
    socket_id = id;
    read_buf_size = dim[1] * 1024 * 1024;
    read_buf = new char[dim[1] * 1024 * 1024];
}
Store::~Store()
{
    delete[] read_buf;
}
void Store::buf_state()
{
    std::cout << "read_buf_state:" << (read_buf_begin - read_buf_end + read_buf_size) % read_buf_size / read_buf_size << std::endl;
}

boolean Store::do_store(char *file, char *dataset, int _store_num, int sec)
{
    std::cout << "sec: " << sec << std::endl;
    store_num = _store_num;
    size_t recv_size = store_num * pluse_size;
    char temp_data[recv_size];

    time_t begin_time, after_time;
    begin_time = time(NULL); //获取时间
    // unpack(buf);
    int ret = 0;

    std::vector<das_data> data_buf;
    do
    {
        after_time = time(NULL);
        recv_data(temp_data, recv_size);
        memcpy(read_buf + ret * recv_size, temp_data, recv_size);
        for (size_t i = 0; i < store_num; i++)
        {
            das_data data = das_data(temp_data + i * pluse_size, pluse_size);
            data_buf.push_back(data);
        }
        // std::cout << "temp:" << int(temp_data[0]) << int(temp_data[1]) << std::endl;

        // write_hdf5(file, dataset, data_buf);
        ret++;
    } while (after_time - begin_time < sec);
    buf_size = ret;
    std::cout << "ret:" << ret << std::endl;
    // } while (ret < 1000);
    return write_hdf5(file, dataset, read_buf);
}

boolean Store::do_store_thread(char *file, char *dataset, int _store_num, int sec)
{

    // // read buf thread
    // recv_data_thread();

    // // uppack data thread
    // unpack(read_buf, index);

    // // store data thread
    // write_hdf5(file, dataset, buf);
}
boolean Store::recv_data(char *buf, int size)
{
    int recv_size = 0;
    while (recv_size < size)
    {
        recv_size += recv(socket_id, buf + recv_size, size - recv_size, 0);

        // std::cout << recv_size << std::endl;
    }
    assert(recv_size == size);
}
boolean Store::recv_data_thread(char *buf, int size)
{
    int recv_size = 0;
    int loop = 0;
    while (1)
    {
        loop++;
        while (recv_size < size)
        {
            recv_size += recv(socket_id, read_buf + read_buf_begin + recv_size, size - recv_size, 0);

            read_buf_begin += recv_size;
            read_buf_begin = read_buf_begin % read_buf_size;
        }
        assert(recv_size == size);
        recv_size = 0;
        if (loop % 10 == 0)
        {
            buf_state();
        }
    }
}
boolean Store::write_hdf5_thread(char *file, char *dataset, char *wdata)
{
    time_t begin_time, after_time;
    int sec = 60;
    begin_time = time(NULL);
    do
    {

        after_time = time(NULL);
    } while (after_time - begin_time < 10);

    while (1)
    {
    }
}

boolean Store::write_hdf5(char *file, char *dataset, char *wdata)
{
    std::cout << "buf_size: " << buf_size << std::endl;
    std::cout << "store_num: " << store_num << std::endl;
    HF5 hf5 = HF5(file, dataset, dim);
    for (size_t i = 0; i < buf_size; i++)
    {
        for (size_t j = 0; j < store_num; j++)
        {
            hf5.extend_write_chunk(dim, &wdata[20 + store_num * pluse_size * i + pluse_size * j]);
        }
    }
    return hf5.close();
}