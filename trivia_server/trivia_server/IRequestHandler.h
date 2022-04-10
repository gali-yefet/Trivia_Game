#pragma once
#include <iostream>
#include <vector>
#include <ctime>

struct RequestInfo
{
	int requestCode;
	std::time_t receivalTime; 
	std::vector<unsigned char> json;
};

struct RequestResult
{
	std::string buffer;
	//IRequestHandler* newHandler;
};

#define SIGN_CODE 6

class IRequestHandler
{
public:
	IRequestHandler() = default;
	virtual bool isRequestRelevant(RequestInfo r) = 0;
	virtual RequestResult handleRequest(RequestInfo r) = 0;

};



