// #include "UsbDas.h"
// #include <cstdio>
// #include <iostream>

// using namespace std;
// UsbDas::UsbDas()
// {
// }

// UsbDas::~UsbDas()
// {
// }
// static UsbDas &get_instance();

// int UsbDas::init()
// {
//     USBDevice = new CCyUSBDevice(NULL);
//     printf("%d\n", USBDevice->DeviceCount());
//     if (!USBDevice->Open(0)) //打开失败
//     {
//         cout << "usb error" << endl;
//     }
//     if (USBDevice->DeviceCount()) //保证至少有一个USB设备连接
//     {
//         for (int i = 0; i < USBDevice->DeviceCount(); i++) //枚举所有USB设备
//         {
//             USBDevice->Open(i);                    //打开第i号USB设备
//             printf("%s\n", USBDevice->DeviceName); //所选择的当前设备名
//             cout << "open usb" << endl;
//         }
//     }
// }

// int UsbDas::recv(char *buf, int len)
// {
//     if (USBDevice == NULL)
//     {
//         return -1;
//     }
//     BulkInEndPt = (CCyBulkEndPoint *)USBDevice->BulkInEndPt;
//     bool res = BulkInEndPt->XferData(buf, len);
//     return res;
// }
