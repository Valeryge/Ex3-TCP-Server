#pragma once
#include "RequestParser.h"

string GetNowTime();
string GetLastModified(string fileName);
string getAppLayer(string filename, int type);
string BuildGetOrHeadResponse(string request, int type);
string BuildPostResponse();
string BuildOptionsResponse(string request);
string BuildTraceResponse(string request);
string BuildErrorResponse(string request);
string BuildTimeoutResponse();
string BuildPutResponse(string request);
string BuildDeleteResponse(string request);
