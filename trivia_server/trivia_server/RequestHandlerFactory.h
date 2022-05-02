#pragma once
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "LoginManager.h"
#include "MenuRequestHandler.h"
#include "RoomManager.h"
//#include "StatisticsManager.h" //TODO: add when adding statistics.

class LoginRequestHandler; //Circular reference

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* db);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();

	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	//StatisticsManager& getStatisticsManager(); //TODO: add when adding statistics.

private:
	IDatabase* m_database;
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	//StatisticsManager* m_statisticsManager; //TODO: add when adding statistics.

};

