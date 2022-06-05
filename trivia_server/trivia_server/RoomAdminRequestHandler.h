#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "GameManager.h"

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(int roomId, std::string username, RoomManager& roomManager, GameManager& gameManager, RequestHandlerFactory& handlerFactory);
	virtual bool isRequestRelevant(RequestInfo r);
	virtual RequestResult handleRequest(RequestInfo r);
	void closeRoom();

private:
	RequestResult closeRoom(RequestInfo r);
	RequestResult startGame(RequestInfo r);
	RequestResult getRoomState(RequestInfo r);

	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;
};

