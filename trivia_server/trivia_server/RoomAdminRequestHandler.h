#pragma once
#include "IRequestHandler.h"

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo r); //TODO
	virtual RequestResult handleRequest(RequestInfo r); //TODO
};

