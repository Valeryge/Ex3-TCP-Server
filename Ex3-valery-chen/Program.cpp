
#include "Program.h"
#include "WebServerFunctions.h"
struct SocketState
{
	SOCKET id;			
	int	recv;			
	int	send;			
	int sendSubType;	
	char buffer[1000];
	int len;
	unsigned int beginCountTimeout;
};
const int MAX_SOCKETS = 60;
const int TIME_PORT = 8080;
const int SEND_TIME = 1;
const int SEND_SECONDS = 2;
int socketsCount = 0;
struct SocketState sockets[MAX_SOCKETS] = { 0 };



void main()
{

	WSAData wsaData;

	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Server: Error at WSAStartup()\n";
		return;
	}


	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == listenSocket)
	{
		cout << "Server: Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	sockaddr_in serverService;
	serverService.sin_family = AF_INET;
	
	serverService.sin_addr.s_addr = INADDR_ANY;
	
	serverService.sin_port = htons(TIME_PORT);

	
	if (SOCKET_ERROR == bind(listenSocket, (SOCKADDR*)&serverService, sizeof(serverService)))
	{
		cout << "Server: Error at bind(): " << WSAGetLastError() << endl;
		closesocket(listenSocket);
		WSACleanup();
		return;
	}

	
	if (SOCKET_ERROR == listen(listenSocket, 5))
	{
		cout << "Server: Error at listen(): " << WSAGetLastError() << endl;
		closesocket(listenSocket);
		WSACleanup();
		return;
	}
	addSocket(listenSocket, LISTEN);

	
	while (true)
	{
		
		fd_set waitRecv;
		FD_ZERO(&waitRecv);
		for (int i = 0; i < MAX_SOCKETS; i++)
		{
			if ((sockets[i].recv == LISTEN) || (sockets[i].recv == RECEIVE))
				FD_SET(sockets[i].id, &waitRecv);
		}

		fd_set waitSend;
		FD_ZERO(&waitSend);
		for (int i = 0; i < MAX_SOCKETS; i++)
		{
			if (sockets[i].send == SEND)
				FD_SET(sockets[i].id, &waitSend);
		}
		int nfd;
		nfd = select(0, &waitRecv, &waitSend, NULL, NULL);
		if (nfd == SOCKET_ERROR)
		{
			cout << "Time Server: Error at select(): " << WSAGetLastError() << endl;
			WSACleanup();
			return;
		}

		timeoutHandler();
		handleWaitingRecv(waitRecv, nfd);
		handleWaitingSend(waitSend, nfd);

	}

	
	cout << "Time Server: Closing Connection.\n";
	closesocket(listenSocket);
	WSACleanup();
}


void handleWaitingRecv(fd_set& waitRecv, int& nfd) {
	for (int i = 0; i < MAX_SOCKETS && nfd > 0; i++)
	{
		if (FD_ISSET(sockets[i].id, &waitRecv))
		{
			nfd--;
			switch (sockets[i].recv)
			{
			case LISTEN:
				acceptConnection(i);
				break;

			case RECEIVE:
				receiveMessage(i);
				break;
			}
		}
	}
}
void handleWaitingSend(fd_set& waitSend, int& nfd) {
	for (int i = 0; i < MAX_SOCKETS && nfd > 0; i++)
	{
		if (FD_ISSET(sockets[i].id, &waitSend))
		{
			nfd--;
			switch (sockets[i].send)
			{
			case SEND:
				sendMessage(i);
				break;
			}
		}
	}

}
bool addSocket(SOCKET id, int what)
{
	for (int i = 0; i < MAX_SOCKETS; i++)
	{
		if (sockets[i].recv == 0)
		{
			sockets[i].id = id;
			sockets[i].recv = what;
			sockets[i].send = IDLE;
			sockets[i].len = 0;
			sockets[i].beginCountTimeout = (unsigned int)GetTickCount();
			socketsCount++;
			return (true);
		}
	}
	return (false);
}

void removeSocket(int index)
{
	sockets[index].recv = 0;
	sockets[index].send = 0;
	sockets[index].beginCountTimeout = 0;
	socketsCount--;
}

void acceptConnection(int index)
{
	SOCKET id = sockets[index].id;
	struct sockaddr_in from;		
	int fromLen = sizeof(from);

	SOCKET msgSocket = accept(id, (struct sockaddr*)&from, &fromLen);
	if (INVALID_SOCKET == msgSocket)
	{
		cout << "Time Server: Error at accept(): " << WSAGetLastError() << endl;
		return;
	}
	cout << "Time Server: Client " << inet_ntoa(from.sin_addr) << ":" << ntohs(from.sin_port) << " is connected." << endl;

	
	unsigned long flag = 1;
	if (ioctlsocket(msgSocket, FIONBIO, &flag) != 0)
	{
		cout << "Server: Error at ioctlsocket(): " << WSAGetLastError() << endl;
	}

	if (addSocket(msgSocket, RECEIVE) == false)
	{
		cout << "\t\tToo many connections, dropped!\n";
		closesocket(id);
	}
	return;
}

void receiveMessage(int index)
{
	SOCKET msgSocket = sockets[index].id;

	int len = sockets[index].len;
	int bytesRecv = recv(msgSocket, &sockets[index].buffer[0], sizeof(sockets[index].buffer) , 0);

	if (SOCKET_ERROR == bytesRecv)
	{
		cout << "Server: Error at recv(): " << WSAGetLastError() << endl;
		closesocket(msgSocket);
		removeSocket(index);
		return;
	}
	if (bytesRecv == 0)
	{
		closesocket(msgSocket);
		removeSocket(index);
		return;
	}
	else
	{
		sockets[index].buffer[bytesRecv] = '\0'; 
		sockets[index].len += bytesRecv;
		sockets[index].send = SEND;

	
	}

}

void sendMessage(int index)
{
	char sendBuff[1000];
	string response;
	SOCKET msgSocket = sockets[index].id;
	string requestType =GetType(sockets[index].buffer);
	int bytesSent = 0;

	if (strcmp(requestType.c_str(), "GET") == 0)
	{
		response = BuildGetOrHeadResponse(sockets[index].buffer, 0);
	}
	else if (strcmp(requestType.c_str(), "POST") == 0)
	{
		cout << getBody(sockets[index].buffer)<< endl;
		response = BuildPostResponse();
	}
	else if (strcmp(requestType.c_str(), "OPTIONS") == 0)
	{
		response = BuildOptionsResponse(sockets[index].buffer);
	}
	else if (strcmp(requestType.c_str(), "TRACE") == 0)
	{
		response = BuildTraceResponse(sockets[index].buffer);
	}
	else if (strcmp(requestType.c_str(), "HEAD") == 0)
	{
		response = BuildGetOrHeadResponse(sockets[index].buffer, 1);
	}
	else if (strcmp(requestType.c_str(), "PUT") == 0)
	{
		response = BuildPutResponse(sockets[index].buffer);
	}
	else if (strcmp(requestType.c_str(), "DELETE") == 0)
	{
		response = BuildDeleteResponse(sockets[index].buffer);
	}
	
	else
	{
		response = BuildErrorResponse(sockets[index].buffer);
	}
	
	strcpy(sendBuff, response.c_str());
	bytesSent = send(msgSocket, sendBuff, (int)strlen(sendBuff), 0);
	if (SOCKET_ERROR == bytesSent)
	{
		cout << "Server: Error at send(): " << WSAGetLastError() << endl;
		return;
	}
	sockets[index].beginCountTimeout= (unsigned int)GetTickCount();

	sockets[index].send = IDLE;
}



void timeoutHandler() {

	string response;
	unsigned int stopTimeout=0;
	
	for (int i = 1; i < MAX_SOCKETS; i++)
	{
		
		if (sockets[i].send != 0 || sockets[i].recv != 0 )
		{
			stopTimeout = (unsigned int)GetTickCount();
			if (stopTimeout - sockets[i].beginCountTimeout >120000) {
				cout << "Server : one of the connections closed!" << endl;
				
				char sendBuff[1000];
				int bytesSent = 0;
				SOCKET msgSocket = sockets[i].id;
				response = BuildTimeoutResponse();
				strcpy(sendBuff, response.c_str());
				sendBuff[response.length() - 1] = 0;
				bytesSent = send(msgSocket, sendBuff, (int)strlen(sendBuff), 0);

				if (SOCKET_ERROR == bytesSent)
				{
					cout << "Server: Error at send(): " << WSAGetLastError() << endl;
					return;
				}
			
				closesocket(sockets[i].id);
				removeSocket(i);
			}
			stopTimeout = 0;
		}
	}
}





