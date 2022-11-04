#include "utils.h"
#include <vector>
#include <stdint.h>
#include <hdf5.h>
#include <H5Cpp.h>
#include "HF5.h"
using namespace std;
int main2()
{
    char file_name[20] = "my_test_file.h5";
    char dataset_name[20] = "my_test_dataset";
    hsize_t dim[2] = {1, 3};
    int data[1][3] = {{1, 1, 3}};
    HF5 myh5 = HF5(file_name, dataset_name, dim, 0);
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

int main(void)
{
    int a = -112;
    printf("%X", a);
    cout << endl;
    time_t nowtime;
    nowtime = time(NULL);    //获取日历时间
    cout << nowtime << endl; //输出nowtime

    struct tm *local, *gm;
    local = localtime(&nowtime); //获取当前系统时间
    dsptime(local);
    gm = gmtime(&nowtime); //获取格林尼治时间
    dsptime(gm);

    return 0;
}
void dsptime(const struct tm *ptm)
{
    char *pxq[] = {"日", "一", "二", "三", "四", "五", "六"};
    cout << ptm->tm_year + 1900 << "年" << ptm->tm_mon + 1 << "月" << ptm->tm_mday << "日 ";
    cout << ptm->tm_hour << ":" << ptm->tm_min << ":" << ptm->tm_sec << " ";
    cout << " 星期" << pxq[ptm->tm_wday] << " 当年的第" << ptm->tm_yday << "天 " << endl;
}
