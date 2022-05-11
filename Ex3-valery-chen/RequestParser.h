#pragma once


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
#pragma comment(lib, "Ws2_32.lib")
#define EMPTY 0
#define LISTEN 1
#define RECEIVE 2
#define IDLE 1
#define SEND 2
#define _GET 1
#define _POST 2
#define _HEAD 3
#define _OPTIONS 4
#define _PUT 5
#define _DELETE 6
#define _TRACE 7
#define _ERROR 8
#define PUT_created 1
#define PUT_modified 2
#define DELETE_success 1
#define DELETE_failed 2
#define MINUTES2 120000
using namespace std;

string GetResource(string request);
string GetLangParameterValue(string request);
const int GetRequestType(string request);
void printBody(string request);