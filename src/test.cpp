#include "utils.h"
#include <vector>
#include <stdint.h>
#include <hdf5.h>
#include <H5Cpp.h>
#include "HF5.h"
#include <iostream>
#include <thread>
using namespace std;
int main2()
{
    char file_name[20] = "my_test_file.h5";
    char dataset_name[20] = "my_test_dataset";
    hsize_t dim[2] = {1, 3};
    int data[1][3] = {{1, 1, 3}};
    HF5 myh5 = HF5(file_name, dataset_name, dim);
    // hsize_t buf[2];
    // myh5.get_dims(buf);
    // cout << "buf:" << buf[0] << " " << buf[1] << endl;
    herr_t status = myh5.extend_write_chunk(dim, data);
    hsize_t buf[2];
    myh5.get_dims(buf);
    cout << "buf:" << buf[0] << " " << buf[1] << endl;
}
#include <iostream>
#include <time.h>
using namespace std;
void dsptime(const struct tm *); //输出时间。

void dsptime(const struct tm *ptm)
{
    char *pxq[] = {"日", "一", "二", "三", "四", "五", "六"};
    cout << ptm->tm_year + 1900 << "年" << ptm->tm_mon + 1 << "月" << ptm->tm_mday << "日 ";
    cout << ptm->tm_hour << ":" << ptm->tm_min << ":" << ptm->tm_sec << " ";
    cout << " 星期" << pxq[ptm->tm_wday] << " 当年的第" << ptm->tm_yday << "天 " << endl;
}
void test_4_8_to_32()
{
    char d1 = (short)0;
    char d2 = (short)0;
    char d3 = (short)0;
    char d4 = (short)230;
    __int32 data_u32 = (d1 << 24) | (d2 << 16) | (d3 << 8) | d4;
    cout << "d:" << d1 << "d:" << d2 << "d:" << data_u32 << endl;
}
void method(int vec[])
{
    // 对vec进行操作
    for (size_t i = 0; i < 5; i++)
    {
        cout << vec[i];
    }
}
int main1(void)
{
    // int vec[5] = {1, 2, 3, 4, 5};
    // thread t(method, &vec);
    // t.detach();

    // test_4_8_to_32();
    // int a = -112;
    // printf("%X", a);
    // cout << endl;
    // time_t nowtime;
    // nowtime = time(NULL);    //获取日历时间
    // cout << nowtime << endl; //输出nowtime

    // struct tm *local, *gm;
    // local = localtime(&nowtime); //获取当前系统时间
    // dsptime(local);
    // gm = gmtime(&nowtime); //获取格林尼治时间
    // dsptime(gm);

    return 0;
}