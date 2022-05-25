#include "RequestParser.h"
string getBody(string request)
{
	int requestSize = request.size();
	char len[1000];
	int BodyLen;
	char body[1000];
	int indexLen = request.find("Content-Length:");
	indexLen += 16;
	int num;
	int k = 0;
	while(request[indexLen]!='\n'&& request[indexLen] != '\r'){
		len[k]= request[indexLen];
		indexLen++;
		k++;
	}
	BodyLen = atoi(len);
	int j = BodyLen;
	for (int i = 0; i < BodyLen+1;i++) {

		body[j]=request[requestSize];
		requestSize--;
		j--;
	}
	return body;
}
string getResource(string request) {

	int i = 0;
	int j = 0;
	string resource;
	while (request[i] != ' ')
	{
		i++;
	}
	i++;
	j = i;
	/*while (request[j] != '?')
	{
		j++;
	}*/
	int indexLen = request.find("?");
	if (indexLen != -1) {
	  resource = request.substr(i, indexLen - i);
	}
	else
	{
		resource = " ";
	}
	return resource;
}

string getFileName(string request) {
	int i = 0;
	int j = 0;
	while (request[i] != ' ')
	{
		i++;
	}
	i++;
	j = i;
	while (request[j] != ' ')
	{
		j++;
	}

	string fileName = request.substr(i, j - i);


	return fileName;
}

string getLangParameterValue(string request) {

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


const int GetRequestType(string request)
{
	string requestType = "";

	int i = 0;
	while (request[i] != ' ')
	{
		i++;
	}
	requestType = request.substr(0, i);

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