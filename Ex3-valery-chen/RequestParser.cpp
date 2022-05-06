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
using namespace std;

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

string GetResource(string request) {

	int i = 0;
	int j = 0;
	while (request[i] != ' ')
	{
		i++;
	}
	while (request[i] != '?')
	{
		j++;
	}
	request.substr(i, j);
	

	return request;
}
string GetLangParameterValue(string request) {

	string valueOfLang = "";
	int indexOfLang = request.find("lang");
	int fromWhichIndex = indexOfLang + 5;
	int toWhichIndex = 0;
	int i = fromWhichIndex;
	while (request[i] != ' ') {
		toWhichIndex++;
		i++;
	}
	valueOfLang = request.substr(fromWhichIndex, toWhichIndex);


	return valueOfLang;
}
 const int GetRequestType(string request) {
	string requestType = "";

	int i = 0;
	while (request[i] != ' ') 
	{
		i++;
	}
	requestType =request.substr(0, i);

	if (!strcmp(requestType.c_str(), "GET"))
	{
		return _GET;
	}
	else if (!strcmp(requestType.c_str(), "POST")) 
	{ 
		return _POST; 
	}
	else if (!strcmp(requestType.c_str(), "HEAD"))
	{ 
		return _HEAD; 
	}
	else if (!strcmp(requestType.c_str(), "OPTIONS")) 
	{ 
		return _OPTIONS; 
	}
	else if (!strcmp(requestType.c_str(), "PUT")) 
	{
		return _PUT; 
	}
	else if (!strcmp(requestType.c_str(), "DELETE"))
	{ 
		return _DELETE; 
	}
	else if (!strcmp(requestType.c_str(), "TRACE")) 	
	{
		return _TRACE;
	}
	else 												
	{
		return _ERROR;
	}

}