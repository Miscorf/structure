#pragma once
#include <time.h>
class das_data
{
private:
    int value = 0;
    unsigned __int16 core_id[2];
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

    unsigned int data_size;
    __int32 end;
    char16_t data[1000];

public:
    das_data(char *buf, int size);
    int check_head(char *head);
    ~das_data();
};
