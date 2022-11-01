#include <winsock2.h> //winsock2的头文件
#include <iostream>
#include <fstream>
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
    ofstream ofs;
    ofs.open("text.txt", ios::out | ios::app);
    for (size_t i = 0; i < len; i++)
    {
        break;
    }
    ofs << hex << c << endl;
    ofs.close();
}