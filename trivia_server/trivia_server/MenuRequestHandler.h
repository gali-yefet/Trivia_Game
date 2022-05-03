#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RoomManager.h"
//#include "StatisticsManager.h" //TODO: add after creating StatisticsManager
#include "RequestHandlerFactory.h"

class RequestHandlerFactory; //Circular reference

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(LoggedUser user, RoomManager& roomManger, RequestHandlerFactory& handlerFactory); //TODO: add StatisticsManager
	virtual bool isRequestRelevant(RequestInfo r);
	virtual RequestResult handleRequest(RequestInfo r); //TODO

private:
	RequestResult getRooms(RequestInfo r);
	RequestResult getPlayesrInRoom(RequestInfo r);
	RequestResult joinRoom(RequestInfo r);
	RequestResult createRoom(RequestInfo r);
	//RequestResult signout(RequestInfo r); //TODO: signout of what?? how?

	//RequestResult getPersonalState(RequestInfo r); //TODO: statistics?
	//RequestResult getHighScore(RequestInfo r); //TODO: how? statistics?

	LoggedUser m_user;
	RoomManager& m_roomManger;
	//StatisticsManager& m_statisticsManager //TODO: add after creating StatisticsManager
	RequestHandlerFactory& m_handlerFactory;
};

