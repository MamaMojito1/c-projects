#include <iostream>
#include <WinSock.h>
#include <stdio.h>
using namespace std;

#define PORT 9909

int nClientSocket;
struct sockaddr_in srv;

int main()
{
	int nRet = 0;
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) < 0)
	{
		cout << "\nWSAStartup failed";
		cin.get();

		WSACleanup();
		exit(EXIT_FAILURE);
	}
	nClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(nClientSocket < 0)
	{
		cout << "\nsocket call failed";
		cin.get();
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);
	srv.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&srv.sin_zero, 0, 8);
	nRet = connect(nClientSocket, (struct sockaddr*) & srv, sizeof(srv));
	if(nRet < 0)
	{
		cout << "\nConnection failed";
		cin.get();
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << "\nConnected to the server";
		char buff[255] = {0, };
		recv(nClientSocket, buff, 255, 0);
		cout << "\n" << "just press enter key to see the the message received from the server.";
		cin.get();
		cout << "\n" << buff;

		cout << "\nNow send your message to server: ";
		while(1)
        {
            fgets(buff, 256, stdin);
            send(nClientSocket, buff, 256, 0);
            cout << "\nPress enter key to get response from server..";
            cin.get();
            recv(nClientSocket, buff, 256, 0);
            cout << "\n" << buff << "\nNow send next message: ";
        }

	}
}
