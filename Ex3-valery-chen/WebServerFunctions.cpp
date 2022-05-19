#include "WebServerFunctions.h"

#pragma comment(lib, "Ws2_32.lib")

//valery
string GetNowTime() {
	char buf[1000];
	time_t now = time(0);
	struct tm tm = *gmtime(&now);
	strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S GMT", &tm);
	return buf;
}
//end valery

string postResponse() {

	string curTimeStr = GetNowTime();
	string appLayer =
		"HTTP/1.1 200 OK\r\n"
		"Date: " + curTimeStr + "\r\n"
		"Server: WebServer\r\n"
		"Content-Type: text/html\r\n"
		"Connection: Keep-Alive\r\n"
		"Content-Length: 35\r\n\r\n"
		"Post request successfully recieved!\n";

	return appLayer;
}

string GetLastModified(string i_FileName) {
	struct stat res;
	stat(i_FileName.c_str(), &res);
	struct tm  time;
	time = *localtime(&res.st_mtime);
	char lastModified[100];
	strftime(lastModified, sizeof(lastModified), "%a, %d %b %Y %X GMT", &time);
	return lastModified;
}

string getAppLayer(string filename) {
	string AppLayer, header, html, htmlSize;

	getline(ifstream(filename), html, '\0');
	html.erase(0, 3); // undisired characters
	htmlSize = to_string(strlen(html.c_str()) - 1);
	if (strcmp(filename.c_str(), "C:\\temp\\Error404.html")) {
		header = "HTTP/1.1 200 OK\r\n";
		
	}
	else {
		header = "HTTP/1.1 404 Not Found\r\n";
	}

	header +="Server: WebServer\r\n"
		"Connection: Keep-Alive\r\n"
		"Date: " + GetNowTime() + "\r\n"
		"Last-Modified: " + GetLastModified(filename) + "\r\n"
		"Content-Type: text/html\r\n"
		"Content-Length: " + htmlSize + "\r\n\r\n";
	AppLayer = header+ html;
	return AppLayer;
}


string BuildGetResponse(string request) {

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

// valery code


string BuildOptionsResponse(string request) {

	string nowTime = GetNowTime();
	string response =
		"HTTP/1.1 200 OK\r\nServer: WebServer\r\nConnection: Keep-Alive\r\n"
		"Date: " + nowTime + "\r\nContent-Type: text/html\r\nContent-Length: 69\r\n"
		"Allow: HEAD, GET, POST, PUT, DELETE, OPTIONS, TRACE\r\n\r\n"
	    "The allowed methods are: HEAD, GET, POST, PUT, DELETE, OPTIONS, TRACE\n";
	return response;
}



string BuildTraceResponse(string request) {
	string nowTime = GetNowTime();

	string response =
		"HTTP/1.1 200 OK\r\nServer: WebServer\r\nConnection: Keep-Alive\r\n"
		"Date: " + nowTime + "\r\n"
		"Content-Type: message/http\r\n"
		"Content-Length: " + to_string(request.length() + 1) + "\r\n\r\n"
		+ request + "\r\n";

	return response;
}

string BuildErrorResponse(string request) {
	string nowTime = GetNowTime();

	string response = 
		"HTTP/1.1 405 Method Not Allowed\r\n"
		"Server: WebServer\r\n"
		"Connection: Keep-Alive\r\n"
		"Date: " + nowTime + "\r\n"
		"Content-Type: text/html\r\n"
		"Content-Length: 88\r\n"
		"Allow: OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE\r\n\r\n"
		"Method Not Allowed\n"
		"The allowed methods are: OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE\n";

	return response;
}

string BuildTimeoutResponse() {
	string nowTime = GetNowTime();

	string response = "HTTP/1.1 408 Request Timeout\r\n"
		"Server: WebServer\r\n"
		"Date: " + nowTime + "\r\n"
		"Connection: close\r\n\r\n\n";

	return response;
}