#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

#include <winsock2.h>
#include <string.h>
#include <fstream>
#include <sstream>

struct SocketState
{
    SOCKET id;			// Socket handle
    int	recv;			// Receiving?
    int	send;			// Sending?
    int sendSubType;	// Sending sub-type
    char buffer[128];
    int len;
};

const int TIME_PORT = 27015;
const int MAX_SOCKETS = 60;
const int EMPTY = 0;
const int LISTEN = 1;
const int RECEIVE = 2;
const int IDLE = 3;
const int SEND = 4;
const int SEND_TIME = 1;
const int SEND_SECONDS = 2;

void main() {

    SocketState* sockets = nullptr;
    sockets = new SocketState[MAX_SOCKETS];

    WSAData wsaData;

    if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        std::cout << "Web Server: Error at WSAStartup()\n";
    }

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (INVALID_SOCKET == listenSocket) {
        std::cout << "Web Server: Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
    }

    sockaddr_in serverService;
    serverService.sin_family = AF_INET;
    serverService.sin_addr.s_addr = INADDR_ANY;
    serverService.sin_port = htons(8080);

    if (SOCKET_ERROR == bind(listenSocket, (SOCKADDR*)&serverService, sizeof(serverService))) {
        std::cout << "Web Server: Error at bind(): " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
    }

    if (SOCKET_ERROR == listen(listenSocket, 5)) {
        std::cout << "Web Server: Error at listen(): " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
    }
    SocketState::addSocket(sockets, listenSocket, LISTEN);

    while (true) {
        fd_set waitRecv;
        FD_ZERO(&waitRecv);
        for (int i = 0; i < MAX_SOCKETS; i++) {
            if ((sockets[i].recv == LISTEN) || (sockets[i].recv == RECEIVE))
                FD_SET(sockets[i].getId(), &waitRecv);
        }

        fd_set waitSend;
        FD_ZERO(&waitSend);
        for (int i = 0; i < MAX_SOCKETS; i++) {
            if (sockets[i].send == SEND)
                FD_SET(sockets[i].getId(), &waitSend);
        }

        int nfd;
        nfd = select(0, &waitRecv, &waitSend, NULL, NULL);
        if (nfd == SOCKET_ERROR) {
            std::cout << "Web Server: Error at select(): " << WSAGetLastError() << std::endl;
            WSACleanup();
        }

        for (int i = 0; i < MAX_SOCKETS && nfd > 0; i++) {
            if (FD_ISSET(sockets[i].getId(), &waitRecv)) {
                nfd--;
                switch (sockets[i].recv) {
                case LISTEN:
                    sockets[i].acceptConnection(sockets);
                    break;

                case RECEIVE:
                    sockets[i].receiveMessage();
                    break;
                }
            }
        }

        for (int i = 0; i < MAX_SOCKETS && nfd > 0; i++) {
            if (FD_ISSET(sockets[i].getId(), &waitSend)) {
                nfd--;
                switch (sockets[i].send) {
                case SEND:
                    sockets[i].sendMessage();
                    break;
                }
            }
        }
    }

    std::cout << "Time Server: Closing Connection.\n";
    closesocket(listenSocket);
    WSACleanup();
}