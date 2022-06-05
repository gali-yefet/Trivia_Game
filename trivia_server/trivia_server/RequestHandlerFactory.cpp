#include "RequestHandlerFactory.h"

/*
create a new factory
in: pointer to db
*/
RequestHandlerFactory::RequestHandlerFactory(IDatabase* db):
    m_database(db), m_loginManager(LoginManager(db)), m_roomManager(RoomManager()), m_statisticsManager(StatisticsManager(db)), m_gameManager(db)
{
}

/*
create a new LoginRequestHandler
in: void
out: LoginRequestHandler
*/
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return  new LoginRequestHandler(m_loginManager, *this);
}

/*
create a new MenuRequestHandler
in: username
out: MenuRequestHandler
*/
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(std::string username)
{
    return new MenuRequestHandler(LoggedUser(username), m_roomManager, m_statisticsManager, *this);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(int roomId, std::string username)
{
    return new RoomAdminRequestHandler(roomId, username, m_roomManager, m_gameManager, *this);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(int roomId, std::string username)
{
    return new RoomMemberRequestHandler(roomId, username, m_roomManager, *this);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(Game m_game, LoggedUser m_user)
{
    return new GameRequestHandler(m_game, m_user, m_gameManager, *this);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return m_roomManager;
}

IDatabase* RequestHandlerFactory::getDatabase()
{
    return m_database;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return m_statisticsManager;
}

GameManager& RequestHandlerFactory::getGameManager()
{
    return m_gameManager;
}
