#include "RequestHandlerFactory.h"

/*
create a new factory
in: pointer to db
*/
RequestHandlerFactory::RequestHandlerFactory(IDatabase* db):
    m_database(db), m_loginManager(LoginManager(db)), m_roomManager(RoomManager())
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
    return new MenuRequestHandler(LoggedUser(username), m_roomManager, *this); //TODO: add statistics
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
