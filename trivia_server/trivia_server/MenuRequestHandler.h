#pragma once
#include "IRequestHandler.h"
class MenuRequestHandler : public IRequestHandler
{
	virtual bool isRequestRelevant(RequestInfo r); //TODO
	virtual RequestResult handleRequest(RequestInfo r); //TODO
};

