#include "Store_h5.h"
#include "assert.h"
#define GB 1024 * 1024 * 1024
Store_h5::Store_h5(SOCKET id, int store_num, hsize_t _dim[])
{
    pluse_size = _dim[1];
    dim[0] = _dim[0];
    dim[1] = _dim[1] - 20 - 4; // 20 开头 4 结尾
    socket_id = id;
    read_buf_size = GB;
    read_buf = new char[read_buf_size];
}
Store_h5::~Store_h5()
{
    delete[] read_buf;
}
void Store_h5::buf_state()
{
    std::cout << "read_buf_state:" << (read_buf_begin - read_buf_end) / read_buf_size << std::endl;
}

boolean Store_h5::do_store(char *file, char *dataset, int _store_num, int sec)
{

    store_num = _store_num;
    size_t recv_size = store_num * pluse_size;
    char temp_data[recv_size];

    time_t begin_time, after_time;
    begin_time = time(NULL); //获取日历时间
    // unpack(buf);
    int ret = 0;

    std::vector<das_data> data_buf;
    do
    {
        after_time = time(NULL);
        recv_data(temp_data, recv_size);
        memcpy(read_buf + ret * recv_size, temp_data, recv_size);
        // for (size_t i = 0; i < store_num; i++)
        // {
        // das_data data = das_data(temp_data + i * pluse_size, pluse_size);
        // data_buf.push_back(data);
        // }
        // std::cout << "temp:" << int(temp_data[0]) << int(temp_data[1]) << std::endl;

        // write_hdf5(file, dataset, data_buf);
        ret++;
    } while (after_time - begin_time < 60);
    buf_size = ret;
    // } while (ret < 1000);
    return write_hdf5(file, dataset, read_buf);
}

boolean Store_h5::do_store_thread(char *file, char *dataset, int _store_num, int sec)
{

    // // read buf thread
    // recv_data_thread();

    // // uppack data thread
    // unpack(read_buf, index);

    // // store data thread
    // write_hdf5(file, dataset, read_buf);
}
boolean Store_h5::recv_data(char *buf, int size)
{
    int recv_size = 0;
    while (recv_size < size)
    {
        recv_size += recv(socket_id, buf + recv_size, size - recv_size, 0);

        std::cout << recv_size << std::endl;
    }

    assert(recv_size == size);
}
boolean Store_h5::recv_data_thread(char *buf, int size)
{
    size_t recv_size = store_num * pluse_size;
    char temp_data[recv_size];
    while (1)
    {
        recv_data(temp_data, size);
        if (read_buf_begin + recv_size > read_buf_size)
        {
            int t_size = read_buf_begin + recv_size - read_buf_size;
            memcpy(read_buf + read_buf_begin, temp_data, t_size);
            read_buf_begin = 0;
            memcpy(read_buf + read_buf_begin, temp_data, t_size);
        }

        memcpy(read_buf + read_buf_begin, temp_data, recv_size);
    }
}

boolean Store_h5::write_hdf5(char *file, char *dataset, std::vector<das_data> wdata)
{
    HF5 hf5 = HF5(file, dataset, dim);
    int d_size = wdata[0].get_data_size();
    int w_size = wdata.size();

    for (size_t i = 0; i < w_size; i++)
    {

        std::vector<uint8_t> *p = &wdata[i].data;
        hf5.extend_write_chunk(dim, p);
    }
    return hf5.close();
}

boolean Store_h5::write_hdf5(char *file, char *dataset, char *wdata)
{
    std::cout << "buf_size: " << buf_size << std::endl;
    HF5 hf5 = HF5(file, dataset, dim);
    for (size_t i = 0; i < buf_size; i++)
    {
        hf5.extend_write_chunk(dim, &wdata[20 + store_num * pluse_size * i]);
        hf5.extend_write_chunk(dim, &wdata[20 + store_num * pluse_size * i + pluse_size]);
        // hf5.extend_write_chunk(dim, &wdata[20 + store_num * pluse_size * i + pluse_size*2]);
        // hf5.extend_write_chunk(dim, &wdata[20 + store_num * pluse_size * i + pluse_size*3]);
        // hf5.extend_write_chunk(dim, &wdata[20 + store_num * pluse_size * i + pluse_size*4]);
        // hf5.extend_write_chunk(dim, &wdata[20 + store_num * pluse_size * i + pluse_size*5]);
        // hf5.extend_write_chunk(dim, &wdata[20 + store_num * pluse_size * i + pluse_size*6]);
        // hf5.extend_write_chunk(dim, &wdata[20 + store_num * pluse_size * i + pluse_size*7]);
    }
    return hf5.close();
}