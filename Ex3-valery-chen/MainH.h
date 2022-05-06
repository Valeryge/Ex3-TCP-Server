#ifndef __Main_H_
#define __Main_H_
#include "RequestParser.h"
#include "WebServerFunctions.h"
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <time.h>
#include <fstream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ctime>

using namespace std;

struct SocketState
{
	SOCKET id;			// Socket handle
	int	recv;			// Receiving?
	int	send;			// Sending?
	int sendSubType;	// Sending sub-type
	char buffer[1000];
	int len;
};
class MainH {



public:

	static void handleWaitingRecv(fd_set& waitRecv, int& nfd);
	static void handleWaitingSend(fd_set& waitSend, int& nfd);
	static bool addSocket(SOCKET id, int what);
	static void removeSocket(int index);
	static void acceptConnection(int index);
	static void receiveMessage(int index);
	static void sendMessage(int index);


};
#endif