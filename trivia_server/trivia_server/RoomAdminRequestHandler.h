#pragma once
#include "IRoomRequestHandler.h"

class RoomAdminRequestHandler : public IRoomRequestHandler
{
public:
	RoomAdminRequestHandler(int roomId, std::string username, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);
	virtual bool isRequestRelevant(RequestInfo r); //TODO
	virtual RequestResult handleRequest(RequestInfo r); //TODO
};

