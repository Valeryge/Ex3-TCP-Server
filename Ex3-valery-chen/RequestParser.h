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
#define IDLE 1
#define SEND 2
#define LISTEN 1
#define RECEIVE 2
using namespace std;

string getResource(string request);
string getLangParameterValue(string request);
string GetType(string request);
string getFileName(string request);
string getBody(string request);