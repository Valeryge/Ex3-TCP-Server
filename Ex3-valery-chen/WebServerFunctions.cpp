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

string BuildPutResponse(string request) {

	
	string filePath = "C:\\temp\\" + getFileName(request);
	string appLayer;
	ifstream theFile(filePath.c_str());


	if (theFile.is_open()) 
	{

		theFile.close();
		appLayer =
			"HTTP/1.1 204 No Content\r\n"
			"Date: " + GetNowTime() + "\r\n"
			"Connection: Keep-Alive\r\n"
			"Server: WebServer\r\n"
			"Content-Type: text/html\r\n"
			"Content-Length: 0\r\n\r\n\n";
	}
	else 
	{

		appLayer =
			"HTTP/1.1 201 Created\r\n"
			"Date: " + GetNowTime() + "\r\n"
			"Connection: Keep-Alive\r\n"
			"Server: WebServer\r\n"
			"Content-Type: text/html\r\n"
			"Content-Length: 33\r\n\r\n"
			"The file was successfully created.\n";

	}
	ofstream file;
	file.open(filePath);
	file << getBody(request);
	file.close();


	return appLayer;
}
string BuildDeleteResponse(string request)
{

  string filePath = "C:\\temp\\" + getFileName(request);
  string appLayer;
  ifstream file(filePath.c_str());

		if (file.is_open()) 
		{
			
			file.close();
			remove(filePath.c_str());
			return appLayer=
				"HTTP/1.1 200 OK\r\n"
				"Date: " + GetNowTime() + "\r\n"
				"Server: WebServer\r\n"
				"Connection: Keep-Alive\r\n"
				"Content-Type: text/html\r\n"
				"Content-Length: 34\r\n\r\n"
				"The file was successfully deleted.\n";
			
		}
		else 
		{
			return appLayer =
				"HTTP/1.1 400 Bad Request\r\n"
				"Date: " + GetNowTime() + "\r\n"
				"Server: WebServer\r\n"
				"Connection: Keep-Alive\r\n"
				"Content-Type: text/html\r\n"
				"Content-Length: 23\r\n\r\n"
				"The file is not exists.\n";
		}

	
}
string postResponse() {


	string appLayer =
		"HTTP/1.1 200 OK\r\n"
		"Date: " + GetNowTime() + "\r\n"
		"Server: WebServer\r\n"
		"Connection: Keep-Alive\r\n"
		"Content-Type: text/html\r\n"
		"Content-Length: 27\r\n\r\n"
		"Your Post request recieved.\n";

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

string getAppLayer(string filename,int type) {
	string AppLayer, header, html;
		int htmlSize;

	getline(ifstream(filename), html, '\0');
	htmlSize = strlen(html.c_str()) - 1;
	if (strcmp(filename.c_str(), "C:\\temp\\Error404.html")==0) {
	
		header = "HTTP/1.1 404 Not Found\r\n";
	}
	else {
		header = "HTTP/1.1 200 OK\r\n";
	}

	header +=
		"Date: " + GetNowTime() + "\r\n"
		"Server: WebServer\r\n"
		"Last-Modified: " + GetLastModified(filename) + "\r\n"
		"Connection: Keep-Alive\r\n"
		"Content-Type: text/html\r\n"
		"Content-Length: " + to_string(htmlSize) + "\r\n\r\n";
	
	if (type== _GET) {
		AppLayer = header + html;
		return AppLayer;
	}
	else {
		return header;
	}
	
	
}


string BuildGetOrHeadResponse(string request,int type) {

	string appLayer;
	string source = getResource(request);
	string parameterLang = getLangParameterValue(request);

	if (strcmp(source.c_str(), "/MyWebsite.html")!=0) {
		appLayer = getAppLayer("C:\\Temp\\Error404.html", type);
	}
	else {
		
		if (strcmp(parameterLang.c_str(), "en")==0|| strcmp(parameterLang.c_str(), "he") == 0|| strcmp(parameterLang.c_str(), "fr") == 0)
		{
			appLayer = getAppLayer("C:\\Temp\\MyWebsite_"+ parameterLang+".html", type);
		}

		else
		{
			appLayer = getAppLayer("C:\\Temp\\Error404.html", type);
		}
	}
	
	return appLayer;
}


// valery code


string BuildOptionsResponse(string request) {

	string nowTime = GetNowTime();
	string response =
		"HTTP/1.1 200 OK\r\nDate: " + nowTime + "\r\nServer: WebServer\r\nConnection: Keep-Alive\r\n"
		"Content-Type: text/html\r\nContent-Length: 69\r\n"
		"Allow: HEAD, GET, POST, PUT, DELETE, OPTIONS, TRACE\r\n\r\n"
	    "The allowed methods are: HEAD, GET, POST, PUT, DELETE, OPTIONS, TRACE\n";
	return response;
}



string BuildTraceResponse(string request) {
	string nowTime = GetNowTime();
	string response =
		"HTTP/1.1 200 OK\r\nDate: " + nowTime + "\r\nServer: WebServer\r\nConnection: Keep-Alive\r\n"
		"Content-Type: message/http\r\n"
		"Content-Length: " + to_string(request.length() + 1) + "\r\n\r\n"
		+ request + "\r\n";

	return response;
}

string BuildErrorResponse(string request) {
	string nowTime = GetNowTime();

	string response = 
		"HTTP/1.1 405 Method Not Allowed\r\n"
		"Date: " + nowTime + "\r\n"
		"Server: WebServer\r\n"
		"Connection: Keep-Alive\r\n"
		"Content-Type: text/html\r\n"
		"Content-Length: 88\r\n"
		"Allow: OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE\r\n\r\n"
		"Method Not Allowed\n"
		"The allowed methods:\n GET\n HEAD\n POST\n PUT\n DELETE\n TRACE\nOPTIONS\n";

	return response;
}

string BuildTimeoutResponse() {
	string nowTime = GetNowTime();

	string response = "HTTP/1.1 408 Request Timeout\r\n"
		"Date: " + nowTime + "\r\n"
		"Server: WebServer\r\n"
		"Connection: close\r\n\r\n\n";

	return response;
}