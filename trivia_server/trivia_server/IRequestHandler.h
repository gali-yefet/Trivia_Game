#pragma once

#include <iostream>
#include <vector>
#include <ctime>

class IRequestHandler; // the RequestResult struct uses this class, so we need to declare it first

typedef struct RequestInfo
{
	int requestCode;
	std::time_t receivalTime; 
	std::vector<unsigned char> json;
}RequestInfo;

typedef struct RequestResult
{
	std::string buffer;
	IRequestHandler* newHandler;
}RequestResult;


class IRequestHandler
{
public:
	IRequestHandler() = default;
	virtual bool isRequestRelevant(RequestInfo r) = 0;
	virtual RequestResult handleRequest(RequestInfo r) = 0;

};
