#include<winsock2.h>//winsock2的头文件
#include<iostream>
#include<fstream>
using namespace std;

//勿忘，链接dll的lib
#pragma comment(lib, "ws2_32.lib")
void ofstr(char c[],int len){
   ofstream ofs;
   ofs.open("text.txt",ios::out|ios::app);
   for (size_t i = 0; i < len; i++)
   {
   
   }
//    git config  user.name  "tyler"  
// git config  user.email  "1291571584@qq.com"
   ofs<<hex<<c<<endl;
   ofs.close();
}
int  main()
{
 //加载winsock2的环境
 WSADATA  wd;
 if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
 {
  cout << "WSAStartup  error：" << GetLastError() << endl;
  return 0;
 }

 //1.创建流式套接字
 SOCKET  s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 if (s == INVALID_SOCKET)
 {
  cout << "socket  error：" << GetLastError() << endl;
  return 0;
 }

 //2.链接服务器
 sockaddr_in   addr;
 addr.sin_family = AF_INET;
 addr.sin_port = htons(24);
 addr.sin_addr.s_addr = inet_addr("192.168.10.16");

 int len = sizeof(sockaddr_in);
 if (connect(s, (SOCKADDR*)&addr, len) == SOCKET_ERROR)
 {
  cout << "connect  error：" << GetLastError() << endl;
  return 0;
 }
 else{
   cout<<"connet right!";
 }

 //3接收服务端的消息

int  ret = 0;
 do
 {
    char buf[100] = { 0 };

    recv(s, buf, 100, 0);
   
   //  char firstNum[32] = {0};
   for (size_t i = 0; i < 100; i++)
   {
      cout<<"i:"<<i<<endl;
      cout <<int(buf[i]) << endl;
      
   }

   //  cout << hex <<int(buf) << endl;

   ofstr(buf);
    ret++;
   //  cout<<ret<<endl;


 } while (ret<10);


// 3随时给服务端发消息

ret = 0;
 do
 {
    char buf[100] = {0};
    cout << "请输入聊天内容:";
    cin >> buf; 
    ret = send(s, buf, 100, 0); 
 } while (ret != SOCKET_ERROR&& ret != 0);


 //4.关闭监听套接字
 closesocket(s);

 //清理winsock2的环境
 WSACleanup();


 return 0;
}