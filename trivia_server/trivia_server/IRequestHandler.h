#pragma once
#define SIGN_CODE 6

#include <iostream>
#include <vector>
#include <ctime>

class IRequestHandler; // the RequestResult struct uses this class, so we need to declare it first

typedef struct RequestInfo
{
	int requestCode;
<<<<<<< HEAD
	std::time_t receivalTime; 
=======
	time_t receivalTime;
>>>>>>> b069233964a4355901da2ed0df2bc141cb10726e
	std::vector<unsigned char> json;
}RequestInfo;

typedef struct RequestResult
{
	std::string buffer;
<<<<<<< HEAD
	//IRequestHandler* newHandler;
};
=======
	IRequestHandler* newHandler;
}RequestResult;
>>>>>>> b069233964a4355901da2ed0df2bc141cb10726e


class IRequestHandler
{
public:
	IRequestHandler() = default;
	virtual bool isRequestRelevant(RequestInfo r) = 0;
	virtual RequestResult handleRequest(RequestInfo r) = 0;

};

