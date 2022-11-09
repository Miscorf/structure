#pragma once
#include <time.h>
#include <vector>
class das_data
{
private:
    unsigned __int32 pluse_id;

    unsigned __int16 year;
    unsigned __int8 month;
    unsigned __int8 day;
    unsigned __int8 hour;
    unsigned __int8 min;
    unsigned __int8 sec;
    unsigned __int8 ms;
    unsigned __int16 us;
    unsigned __int16 valid;
    int value = 0;
    unsigned __int16 core_id[2];
    unsigned int data_size;
    __int32 end;

public:
    std::vector<uint8_t> data;
    das_data(char *buf, int size);
    int get_data_size();
    std::vector<uint8_t> get_data();
    int check_head(char *head);
    ~das_data();
};
