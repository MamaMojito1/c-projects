#include <iostream>
#include <WinSock.h>
#include <conio.h>
using namespace std;
#define PORT 9909

struct sockaddr_in srv;
fd_set fr, fw, fe;
int nMaxFd;
int nSocket;
int nArrClient[5];

void ProcessNewMessage(int nClientSocket)
{
    cout << "\nProcessing the new message for client socket: " << nClientSocket;
    char buff[256+1] = {0, };
    int nRet = recv(nClientSocket, buff, 256, 0);
    if(nRet < 0)
    {
        cout << "\nSomething wrong happened..closing the connection for client";
        closesocket(nClientSocket);
        for(int nIndex = 0;nIndex < 5;nIndex++)
        {
            if(nArrClient[nIndex] == nClientSocket)
            {
                nArrClient[nIndex] = 0;
                break;
            }
        }
    }
    else
    {
        cout << "\nThe message received from the client is: " << buff;
        //send response to the client
        send(nClientSocket, "Processed your request", 23, 0);
        cout << "\n*****************************************************";

    }
}

void ProcessTheNewRequests()
{
    //New Connection request
	if(FD_ISSET(nSocket, &fr))
	{
	    int nLen = sizeof(struct sockaddr);
	    int nClientSocket = accept(nSocket, NULL, &nLen);
	    if(nClientSocket > 0)
        {
            //put it into the client fd_set.
            int nIndex;
            for ( nIndex = 0; nIndex < 5;nIndex++)
            {
                if(nArrClient[nIndex] == 0)
                {
                    nArrClient[nIndex] = nClientSocket;
                    send(nClientSocket, "Got The Connection done successfully.", 37, 0); // third argument is the length of your message which is in this case 37. max can 255
                    break;
                }
            }
            if(nIndex == 5)
            {
                cout << "\nNo space for new connection.";
            }
        }
	}
	else
    {
        for(int nIndex = 0;nIndex < 5;nIndex++)
        {
            if(FD_ISSET(nArrClient[nIndex], &fr))
            {
                //got the new message from the client
                //just recv new message
                // just queue that for new workes of your server to fulfill the request
                ProcessNewMessage(nArrClient[nIndex]);
            }
        }
    }
}

int main()
{
	int nRet = 0;
	WSADATA ws;
	if(WSAStartup(MAKEWORD(2, 2), &ws) < 0)
	{
		cout << "\nWSA Failed to initialize!\n";
	}
	else
	{
		cout << "\nWSA initialize successfully!\n";
	}

	//initialize the socket
	nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if( nSocket < 0 )
	{
		cout << "\nThe socket not opened";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << "The socket opened successfully " << nSocket;
	}

	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);
	srv.sin_addr.s_addr = INADDR_ANY;
	memset(&(srv.sin_zero), 0, 8);

	//set socket
	int nOptVal = 0;
	int nOptLen = sizeof(nOptVal);
	nRet = setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR, (const char *)&nOptVal, nOptLen);
	if (!nRet)
	{
		cout << "\nThe set sockopt call successful.";
	}
	else
	{
		cout << "\nThe set sockopt call failed.\n";
		WSACleanup();
		exit(EXIT_FAILURE);
	}

	//about blocking vs non-blocking sockets



	//bind the socket to the local port
	nRet = bind(nSocket, (sockaddr*)&srv, sizeof(sockaddr));
	if(nRet < 0)
	{
		cout << "\nFail to bind to local port";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << "\nSucessfully bind to local port";
	}

	nRet = listen(nSocket, 5);
	if(nRet < 0)
	{
		cout << "\nFail to start listen to local port";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << "\nStarted listening to local port\n";
	}
	nMaxFd = nSocket;
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	FD_ZERO(&fr);
	FD_ZERO(&fw);
	FD_ZERO(&fe);

	FD_SET(nSocket, &fr);
	FD_SET(nSocket, &fe);

	while(1)
	{
		FD_ZERO(&fr);
		FD_ZERO(&fw);
		FD_ZERO(&fe);

		FD_SET(nSocket, &fr);
		FD_SET(nSocket, &fe);

		for(int nIndex = 0;nIndex < 5;nIndex++)
        {
            if(nArrClient[nIndex] != 0)
            {
                FD_SET(nArrClient[nIndex], &fr);
                FD_SET(nArrClient[nIndex], &fe);
            }
        }

		//Keep waiting for new requests and proceed as per the request

		nRet = select(nMaxFd+1, &fr, &fw, &fe, &tv);
		if(nRet > 0)
		{
			//When someone connects or communicate with a message over
			//a dedicated connection

			//please remember that the socket listening	to new clients
			//and then communicating with the same client later and not the same.
			//after connection you get one more socket to communicate with client
			//you need to send/receive message over the network using that new socket
			cout << "\nData on port...Processing now";
			ProcessTheNewRequests();
		}
		else if(nRet == 0)
		{
			//No connection or any communication request made or you can
			//say that none of the sockets description
		}
		else
		{
            WSACleanup();
			exit(EXIT_FAILURE);
		}

		//cout << "\n" << "After select call: " << fr.fd_count << "\n";
		//Sleep(2000);
	}

	cin.get();
	return 0;
}
