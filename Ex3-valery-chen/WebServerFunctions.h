#pragma once
#include "RequestParser.h"

string GetNowTime();
string GetLastModified(string fileName);
string getAppLayer(string filename, int type);
string BuildGetOrHeadResponse(string request, int type);
string postResponse();
string BuildOptionsResponse(string request);
string BuildTraceResponse(string request);
string BuildErrorResponse(string request);
string BuildTimeoutResponse();
string BuildPutResponse(string request);
string GetPutAppLayer(string fileName);
//string BuildHeadResponse(string request);