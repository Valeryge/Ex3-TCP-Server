#ifndef __RequestParser_H_
#define __RequestParser_H_
#include "MainH.h"
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

class RequestParser
{

public:

	static const int GetRequestType(string request);
	static string GetResource(string request);
	static string GetLangParameterValue(string request);


};
#endif