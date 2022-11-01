#include <stdio.h>
#include <unistd.h>
#include <winsock2.h>
#include <sys/types.h>
#include "windows.h" //一定要包含该头文件
// #include <sys/socket.h>
#include <string.h>
#include <ctype.h>
#include <ws2tcpip.h>
#include <string.h>
// #include <arpa/inet.h>

#define SERVER_PORT 80

void do_http_request(int client_sock);
int get_line(int sock, char *buf, int size);
const static int debug = 1;
int main(void)
{

    int sock; //代表信箱
    struct sockaddr_in server_addr;

    // 1.美女创建信箱
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // 2.清空标签，写上地址和端口号
    memset(&server_addr,0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;                //选择协议族IPV4
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //监听本地所有IP地址
    server_addr.sin_port = htons(SERVER_PORT);       //绑定端口号

    //实现标签贴到收信得信箱上
    bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    //把信箱挂置到传达室，这样，就可以接收信件了
    listen(sock, 128);

    //万事俱备，只等来信
    printf("等待客户端的连接\n");

    int done = 1;

    while (done)
    {
        struct sockaddr_in client;
        int client_sock, len, i;
        char client_ip[64];
        char buf[256];

        socklen_t client_addr_len;
        client_addr_len = sizeof(client);
        client_sock = accept(sock, (struct sockaddr *)&client, &client_addr_len);

        // 打印客服端IP地址和端口号


        /*处理http请求*/
        do_http_request(client_sock);
        close(client_sock);
        
    }
    close(sock);
    return 0;
}
int get_line(int sock, char *buf, int size){
	int count = 0;
	char ch = '\0';
	int len = 0;
	
	
	while( (count<size - 1) && ch!='\n'){
		len = read(sock, &ch, 1);
		
		if(len == 1){
			if(ch == '\r'){
				continue;
			}else if(ch == '\n'){
				//buf[count] = '\0';
				break;
			}
			
			//这里处理一般的字符
			buf[count] = ch;
			count++;
			
		}else if( len == -1 ){//读取出错
			perror("read failed");
			count = -1;
			break;
		}else {// read 返回0,客户端关闭sock 连接.
			fprintf(stderr, "client close.\n");
			count = -1;
			break;
		}
	}
	
	if(count >= 0) buf[count] = '\0';
	
	return count;
}

void do_http_request(int client_sock){

	int len = 0;
	char buf[256];
	char method[64];
	char url[256];
	char path[256];

	/*读取客户端发送的http 请求*/
	
	//1.读取请求行
	len = get_line(client_sock, buf, sizeof(buf));
	
	if(len > 0){//读到了请求行
		int i=0, j=0;
		while(!isspace(buf[j]) && (i<sizeof(method)-1)){
			method[i] = buf[j];
			i++;
			j++;
		}
		
		method[i] = '\0';
		if(debug) printf("request method: %s\n", method);
		
		if(strncasecmp(method, "GET", i)==0){ //只处理get请求
	        if(debug) printf("method = GET\n");
		
		    //获取url
		    while(isspace(buf[j++]));//跳过白空格
		    i = 0;
		
		    while(!isspace(buf[j]) && (i<sizeof(url)-1)){
			    url[i] = buf[j];
			    i++;
			    j++;
		    }
		
		    url[i] = '\0';
		
		    if(debug) printf("url: %s\n", url);
			
			//继续读取http 头部
		    do{
			    len = get_line(client_sock, buf, sizeof(buf));
			    if(debug) printf("read: %s\n", buf);
			
		    }while(len>0);
			
			//***定位服务器本地的html文件***
			
			//处理url 中的?
			{
				char *pos = strchr(url, '?');
				if(pos){
					*pos = '\0';
					printf("real url: %s\n", url);
				}
			}
			
			sprintf(path, "./html_docs/%s", url);
			if(debug) printf("path: %s\n", path);
			
			//执行http 响应
	
	    }else {
//非get请求, 读取http 头部，并响应客户端 501 	Method Not Implemented
			fprintf(stderr, "warning! other request [%s]\n", method);
			do{
			    len = get_line(client_sock, buf, sizeof(buf));
			    if(debug) printf("read: %s\n", buf);
			
		    }while(len>0);
			
			//unimplemented(client_sock);   //在响应时再实现
			
		}
		
		
		
		
		
	}else {//请求格式有问题，出错处理
		//bad_request(client_sock);   //在响应时再实现
	}
	
	
	
	
	
}

