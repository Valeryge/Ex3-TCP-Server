#ifndef __WebServerFunctions_H_
#define __WebServerFunctions_H_
#include "RequestParser.h"
#include "MainH.h"

class WebServerFunctions {

public:
	static string GetTime();
	static string GetLastModified(string fileName);
	static string getHTTPAppLayer(string filename);
	static string GetResponse(string request);
};
#endif