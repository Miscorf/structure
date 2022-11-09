#include <iostream>

#include "das_data.h"
#include "utils.h"

// 初始化 data 并解包
das_data::das_data(char *buf, int size)
{
    if (check_head(buf))
    {

        value = true;
        core_id[0] = uint8_t(buf[2]);
        core_id[1] = uint8_t(buf[3]);
        pluse_id = (uint8_t(buf[4]) << 24) | (uint8_t(buf[5]) << 16) | (uint8_t(buf[6]) << 8) | uint8_t(buf[7]);
        year = (uint8_t(buf[8]) << 8) | uint8_t(buf[9]);
        month = uint8_t(buf[10]);
        day = uint8_t(buf[11]);
        hour = uint8_t(buf[12]);
        min = uint8_t(buf[13]);
        sec = uint8_t(buf[14]);
        ms = uint8_t(buf[15]);
        us = (uint8_t(buf[16]) << 8) | uint8_t(buf[17]);
        valid = (uint8_t(buf[18]) << 8) | uint8_t(buf[19]);

        std::cout << " buf:" << uint8_t(buf[8]) << "buf:" << uint8_t(buf[9]) << std::endl;
        data.assign(buf + 20, buf + size - 4);
        // utc time is  8-18 char
        data_size = size - 20 - 4;
        std::cout << " pluse:" << pluse_id << "year:" << year << std::endl;
    }
    else
    {
        std::cout << "check error!";
    }
}

// check head -> EB90 = -21,-112
int das_data::check_head(char *head)
{

    if (int(head[0]) == -21 && int(head[1]) == -112)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int das_data::get_data_size()
{
    return data_size;
}

std::vector<uint8_t> das_data::get_data()
{
    return data;
}
das_data::~das_data()
{
}