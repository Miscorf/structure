#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>

using namespace std;

//添加动态库的lib
#pragma comment(lib, "ws2_32.lib")

int main()
{
	SOCKET m_Socket;
	SOCKADDR_IN m_RemoteAddress; //远程地址
	int m_RemoteAddressLen;

	// socket环境
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "WSAStartup error:" << GetLastError() << endl;
		return false;
	}

	// socket对象
	m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_Socket == INVALID_SOCKET)
	{
		closesocket(m_Socket);
		m_Socket = INVALID_SOCKET;
		return false;
	}

	// 远端地址
	int port = 24;
	m_RemoteAddress.sin_family = AF_INET;
	m_RemoteAddress.sin_port = htons(port);
	m_RemoteAddressLen = sizeof(m_RemoteAddress);
	m_RemoteAddress.sin_addr.S_un.S_addr = inet_addr("192.168.10.16");

	// inet_pton(AF_INET, ip, &m_RemoteAddress.sin_addr);

	// 接收和发送
	char recvBuf[1024] = {0};
	char sendBuf[1024] = "FFC00001FFFE0002";

	while (1)
	{
		int sendLen = sendto(m_Socket, sendBuf, strlen(sendBuf), 0, (sockaddr *)&m_RemoteAddress, m_RemoteAddressLen);
		if (sendLen > 0)
		{
			std::printf("发送到远程端连接, 其ip: %s, port: %d\n", inet_ntoa(m_RemoteAddress.sin_addr), ntohs(m_RemoteAddress.sin_port));
			cout << "发送到远程端的信息： " << sendBuf << endl;
		}

		int recvLen = recvfrom(m_Socket, recvBuf, 1024, 0, NULL, NULL);
		if (recvLen > 0)
		{
			std::printf("接收到一个连接, 其ip: %s, port: %d\n", inet_ntoa(m_RemoteAddress.sin_addr), ntohs(m_RemoteAddress.sin_port));
			cout << "接收到一个信息： " << recvBuf << endl;
		}
	}

	closesocket(m_Socket);
	WSACleanup();
	return true;
}
