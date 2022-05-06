#pragma once
#include "RequestParser.cpp"



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
string getHTTPAppLayer(string i_Filename) {
	string HTTPAppLayer, headerContent, htmlContent, htmlContentSize;
	string curTimeStr = GetTime();
	string lastModified = GetLastModified(i_Filename);

	getline(ifstream(i_Filename), htmlContent, '\0');
	htmlContent.erase(0, 3); // undisired characters
	htmlContentSize = to_string(strlen(htmlContent.c_str()) - 1);
	if (!strcmp(i_Filename.c_str(), "C:\\temp\\site_404.html")) {
		headerContent = "HTTP/1.1 404 Not Found\r\n";
	}
	else {
		headerContent = "HTTP/1.1 200 OK\r\n";
	}

	headerContent +=
		"Server: WebServer\r\n"
		"Connection: Keep-Alive\r\n"
		"Date: " + curTimeStr + "\r\n"
		"Last-Modified: " + lastModified + "\r\n"
		"Content-Type: text/html\r\n"
		"Content-Length: " + htmlContentSize + "\r\n\r\n";

	return headerContent + htmlContent;
}


string GetResponse(string i_Request) {

	string HTTPAppLayer;
	string source = GetResource(i_Request);
	string parameterLang = GetLangParameterValue(i_Request);

	if (!strcmp(source.c_str(), "/site.html")) {
		if (!strcmp(parameterLang.c_str(), "en")) HTTPAppLayer = getHTTPAppLayer("C:\\temp\\en_site.html");
		else if (!strcmp(parameterLang.c_str(), "he")) HTTPAppLayer = getHTTPAppLayer("C:\\temp\\he_site.html");
		else if (!strcmp(parameterLang.c_str(), "fr")) HTTPAppLayer = getHTTPAppLayer("C:\\temp\\fr_site.html");
		else										   HTTPAppLayer = getHTTPAppLayer("C:\\temp\\site_404.html");
	}
	else {
		HTTPAppLayer = getHTTPAppLayer("C:\\temp\\site_404.html");
	}

	return HTTPAppLayer;
}

