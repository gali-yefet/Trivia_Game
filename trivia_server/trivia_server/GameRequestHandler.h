#pragma once
#include "IRequestHandler.h"
class GameRequestHandler : public IRequestHandler
{
	virtual bool isRequestRelevant(RequestInfo r); //TODO
	virtual RequestResult handleRequest(RequestInfo r); //TODO
};

