#pragma once
#include "RequestParser.h"
void receiveMessage(int index);
void sendMessage(int index);
void acceptConnection(int index);
void handleWaitingRecv(fd_set& waitRecv, int& nfd);
void handleWaitingSend(fd_set& waitSend, int& nfd);
bool addSocket(SOCKET id, int what);
void removeSocket(int index);