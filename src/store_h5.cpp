#include "Store_h5.h"
#include "assert.h"
#define gb 6 * 1024 * 1024 * 1024
Store_h5::Store_h5(SOCKET id, int store_num, hsize_t _dim[])
{
    pluse_size = _dim[1];
    dim[0] = _dim[0];
    dim[1] = _dim[1] - 20 - 4; // 20 开头 4 结尾
    socket_id = id;
    bufp = new char[100000000];
}
Store_h5::~Store_h5()
{
    delete []bufp;
}
boolean Store_h5::do_store(char *file, char *dataset, int _store_num, int sec)
{
    store_num = _store_num;
    size_t recv_size = store_num * pluse_size;
    char temp_data[recv_size+5];

    time_t begin_time, after_time;
    begin_time = time(NULL); //获取日历时间
    // unpack(buf);
    int ret = 0;

    std::vector<das_data> data_buf;
    do
    {
        after_time = time(NULL);
        recv_data(temp_data, recv_size);
        memcpy(bufp + ret * recv_size, temp_data, recv_size);
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
    return write_hdf5(file, dataset, bufp);
}
boolean Store_h5::recv_data(char *buf, int size)
{
    int c = recv(socket_id, buf, size, 0);
    if (c!=size)
    {
        std::cout<<c<<std::endl;
    }
    
    // assert(c==size);
    return c;
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