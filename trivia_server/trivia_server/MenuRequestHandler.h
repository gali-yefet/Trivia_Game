#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory; //Circular reference

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(LoggedUser user, RoomManager& roomManger, StatisticsManager& statisticsManager, RequestHandlerFactory& handlerFactory);
	virtual bool isRequestRelevant(RequestInfo r);
	virtual RequestResult handleRequest(RequestInfo r);

private:
	RequestResult getRooms(RequestInfo r);
	RequestResult getPlayesrInRoom(RequestInfo r);
	RequestResult joinRoom(RequestInfo r);
	RequestResult createRoom(RequestInfo r);
	RequestResult signout(RequestInfo r);
	RequestResult getPersonalStats(RequestInfo r);
	RequestResult getHighScore(RequestInfo r);

	LoggedUser m_user;
	RoomManager& m_roomManger;
	StatisticsManager& m_statisticsManager;
	RequestHandlerFactory& m_handlerFactory;
};

