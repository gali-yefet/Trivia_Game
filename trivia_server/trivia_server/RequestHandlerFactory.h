#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "GameManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "GameRequestHandler.h"

//Circular reference
class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* db);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(std::string username);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(int roomId, std::string username);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(int roomId, std::string username);
	GameRequestHandler* createGameRequestHandler(Room room, LoggedUser user);

	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	IDatabase* getDatabase();
	StatisticsManager& getStatisticsManager();
	GameManager& getGameManager();

private:
	IDatabase* m_database;
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	GameManager m_gameManager;
	StatisticsManager m_statisticsManager;

};

