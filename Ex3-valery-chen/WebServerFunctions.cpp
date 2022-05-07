#include "WebServerFunctions.h"

#pragma comment(lib, "Ws2_32.lib")
string GetTime() {
	time_t timer = time(nullptr);
	struct tm  tstruct;
	tstruct = *localtime(&timer);
	char curTime[100];
	strftime(curTime, sizeof(curTime), "%a, %d %b %Y %X GMT", &tstruct);
	string curTimeStr = curTime;
	return curTimeStr;
}

string GetLastModified(string i_FileName) {
	struct stat result;
	stat(i_FileName.c_str(), &result);
	struct tm  tstruct;
	tstruct = *localtime(&result.st_mtime);
	char lastModified[100];
	strftime(lastModified, sizeof(lastModified), "%a, %d %b %Y %X GMT", &tstruct);
	string lastModifiedStr = lastModified;
	return lastModifiedStr;
}
string getAppLayer(string filename) {
	string AppLayer, header, html, htmlSize;
	string curTimeStr = GetTime();
	string lastModified = GetLastModified(filename);

	getline(ifstream(filename), html, '\0');
	html.erase(0, 3); // undisired characters
	htmlSize = to_string(strlen(html.c_str()) - 1);
	if (strcmp(filename.c_str(), "C:\\temp\\Error404.html")) {
		header = "HTTP/1.1 200 OK\r\n";
		
	}
	else {
		header = "HTTP/1.1 404 Not Found\r\n";
	}

	header +=
		"Server: WebServer\r\n"
		"Connection: Keep-Alive\r\n"
		"Date: " + curTimeStr + "\r\n"
		"Last-Modified: " + lastModified + "\r\n"
		"Content-Type: text/html\r\n"
		"Content-Length: " + htmlSize + "\r\n\r\n";
	AppLayer = header+ html;
	return AppLayer;
}


string GetResponse(string request) {

	string appLayer;
	string source = GetResource(request);
	string parameterLang = GetLangParameterValue(request);

	if (strcmp(source.c_str(), "/site.html")!=0) {
		appLayer = getAppLayer("C:\\Temp\\Error404.html");
	}
	else {
		
		if (strcmp(parameterLang.c_str(), "en")==0)
		{
			appLayer = getAppLayer("C:\\Temp\\MyWebsite_en.html");
		}
		else if (strcmp(parameterLang.c_str(), "he")==0)
		{
			appLayer = getAppLayer("C:\\Temp\\MyWebsite_he.html");
		}
		else if (strcmp(parameterLang.c_str(), "fr")==0)
		{
			appLayer = getAppLayer("C:\\Temp\\MyWebsite_fr.html");
		}
		else
		{
			appLayer = getAppLayer("C:\\Temp\\Error404.html");
		}
	}

	return appLayer;
}

