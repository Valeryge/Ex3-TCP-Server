
#include "RequestParser.h"

string RequestParser::GetResource(string request) {

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
string RequestParser::GetLangParameterValue(string request) {

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


const int RequestParser::GetRequestType(string request)
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
