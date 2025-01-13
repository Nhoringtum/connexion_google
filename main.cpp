#include "WinSock2.h"
#include "ws2tcpip.h"
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSADATA data;
	WSAStartup(MAKEWORD(2, 2), &data);

	SOCKET client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in server;
	if (client_socket == INVALID_SOCKET)
	{
		std::cout << "Erreur creation socket : " << WSAGetLastError() << std::endl;
		return 0;
	}

	if (inet_pton(AF_INET, "192.168.1.21", &server.sin_addr) <= 0)
	{
		return false;
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(80);
	if(connect(client_socket, reinterpret_cast<const sockaddr*>(&server), sizeof(server)) != SOCKET_ERROR)
	{

	}

	char s_buffer[] = "GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n";
	int s_count = send(client_socket, s_buffer, strlen(s_buffer), 0);
	//int e = WSAGetLastError();
	
	if (s_count == -1)
	{
		std::cout << "oskour" << std::endl;
	}
	std::cout << s_count << std::endl;

	int r_count = recv(client_socket, s_buffer, strlen(s_buffer), 0);
	if (r_count <= 0)
	{
		std::cout << "oskour1" << std::endl;
	}

	std::cout << r_count << std::endl;

	closesocket(client_socket);
	WSACleanup();
	return 0;
}