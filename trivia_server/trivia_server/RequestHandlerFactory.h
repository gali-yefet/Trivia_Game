#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"

//Circular reference
class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* db);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(std::string username);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(int roomId, std::string username);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(int roomId, std::string username);


	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	IDatabase* getDatabase();
	StatisticsManager& getStatisticsManager();

private:
	IDatabase* m_database;
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;

};

