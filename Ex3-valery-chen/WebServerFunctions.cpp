
#include "WebServerFunctions.h"


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
	
	string time = GetTime();
	string lastModified = GetLastModified(filename);
	string appLayer, header, html, htmlSize;

	getline(ifstream(filename), html, '\0');
	html.erase(0, 3); 
	htmlSize = to_string(strlen(html.c_str()) - 1);

	if (strcmp(filename.c_str(), "C:\\temp\\site_404.html")!=0) 
	{
		header = "HTTP/1.1 200 OK\r\n";
		
	}
	else 
	{
		header = "HTTP/1.1 404 Not Found\r\n";
	}

	header +=
		"Server: WebServer\r\n"
		"Connection: Keep-Alive\r\n"
		"Date: " + time + "\r\n"
		"Last-Modified: " + lastModified + "\r\n"
		"Content-Type: text/html\r\n"
		"Content-Length: " + htmlSize + "\r\n\r\n";
	appLayer = header + html;
	return appLayer;
}


string GetResponse(string request) {

	string appLayer;
	string source = GetResource(request);
	string parameterLang = GetLangParameterValue(request);

	if (strcmp(source.c_str(), "/site.html")!=0) 
	{
		appLayer = getAppLayer("C:\\temp\\site_404.html");
	}
	else {
		
		if (strcmp(parameterLang.c_str(), "en") == 0)
		{
			appLayer = getAppLayer("C:\\temp\\en_site.html");
		}
		else if (strcmp(parameterLang.c_str(), "he") == 0)
		{
			appLayer = getAppLayer("C:\\temp\\he_site.html");
		}
		else if (strcmp(parameterLang.c_str(), "fr") == 0)
		{
			appLayer = getAppLayer("C:\\temp\\fr_site.html");
		}
		else
		{
			appLayer = getAppLayer("C:\\temp\\site_404.html");
		}
	}

	return appLayer;
}

