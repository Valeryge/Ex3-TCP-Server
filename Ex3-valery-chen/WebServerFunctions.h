#pragma once
#include "RequestParser.h"

string GetNowTime();
string GetLastModified(string fileName);
string getAppLayer(string filename);
string BuildGetResponse(string request);
string postResponse();
string BuildOptionsResponse(string request);
string BuildTraceResponse(string request);
string BuildErrorResponse(string request);
string BuildTimeoutResponse();