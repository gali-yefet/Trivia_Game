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
out: void
*/
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return  new LoginRequestHandler(m_loginManager, *this);
}

/*
create a new MenuRequestHandler
in: void
out: void
*/
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
    return new MenuRequestHandler(); //TODO: change after actualy making MenuRequestHandler
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return m_roomManager;
}
