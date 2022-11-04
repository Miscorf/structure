#include "Unpack.h"

#define MAX_PLUSE_SIZE 1000 // 每个脉冲最大字节数

Unpack::Unpack(SOCKET id)
{
    socket_id = id;
}
boolean Unpack::check_next_pluse()
{
    // 查看下一个buf是否EB90开头
    char check_buf[pluse_size];
    int recv_data_size = recv(socket_id, check_buf, pluse_size, 0);
    std::cout << "check:";
    std::cout << int(check_buf[0]) << " " << int(check_buf[1]) << std::endl;
    int ret = 0;
    std::cout << "pluse_size:" << pluse_size << std::endl;
    if (int(check_buf[0]) == -21 && int(check_buf[0]) == -112)
    {
        return true;
    }
    return false;
}

// 获取两个ep90之间的间隔 ep90_size
boolean Unpack::clear()
{
    // 获取两个ep90之间的间隔 ep90_size
    int pack_max_size = MAX_PLUSE_SIZE;
    char find_size_buf[pack_max_size] = {0};
    int recv_data_size = recv(socket_id, find_size_buf, pack_max_size, 0);
    int ep90_size = EP90_size(find_size_buf, pack_max_size);
    pluse_size = ep90_size;
    //按ep90_size读取每个脉冲
    //读取第一个ep90位置，并对第二个脉冲丢弃该位置前的缓冲
    char find_flag_buf[ep90_size] = {0};
    recv_data_size = recv(socket_id, find_flag_buf, ep90_size, 0);
    int flag = findEB90_0000(find_flag_buf, ep90_size);

    // 丢弃flag之前的buf
    char drop_buf[flag] = {0};
    recv_data_size = recv(socket_id, drop_buf, flag, 0);
    return check_next_pluse();
}

int Unpack::get_pluse_size()
{
    return pluse_size;
}

Unpack::~Unpack()
{
}
