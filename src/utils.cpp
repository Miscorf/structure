#include <winsock2.h> //winsock2的头文件
#include <iostream>
#include "utils.h"
using namespace std;

// 查找eb90所在char中的位置，-1代表没找到
int findEB90_0000(char c[], int len)
{
    for (size_t i = 0; i < len; i++)
    {
        if (int(c[i]) == -21)
        {
            if (c[i + 1] == -112)
                return i;
        }
    }
    return -1;
}
int EP90_size(char c[], int len)
{
    for (size_t i = 0; i < len; i++)
    {
        if (int(c[i]) == -21)
        {
            if (int(c[i + 1]) == -112)
            {
                int k = i;
                for (size_t j = i + 1; j < len; j++)
                {
                    if (int(c[j]) == -21)
                    {
                        if (int(c[j + 1] == -112))
                        {
                            return j - k;
                        }
                    }
                }
            }
        }
    }
    return -1;
}

void ofstr(char c[], int len)
{
}

int32_t change_4int8_to_int32(char buf[])
{
    __int8 d1 = buf[0];
    __int8 d2 = buf[1];
    __int8 d3 = buf[2];
    __int8 d4 = buf[3];
    __int32 res = (d1 << 24) | (d2 << 16) | (d3 << 8) | d4;
    return res;
}