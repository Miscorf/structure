#ifndef _UNPACK_H
#define _UNPACK_H

#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <vector>

#include "utils.h"

// 解包、处理数据报类
class Unpack
{
private:
    SOCKET socket_id;
    int pluse_size;

public:
    Unpack(SOCKET id);
    boolean clear();
    int get_pluse_size();
    boolean check_next_pluse();
    boolean do_unpack(char *buf);
    ~Unpack();
};

#endif