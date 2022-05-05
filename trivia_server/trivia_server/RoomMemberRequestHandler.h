#pragma once
#include "IRequestHandler.h"

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo r); //TODO
	virtual RequestResult handleRequest(RequestInfo r); //TODO
};

