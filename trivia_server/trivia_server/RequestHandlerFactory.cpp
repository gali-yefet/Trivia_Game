#include "RequestHandlerFactory.h"

/*
create a new factory
in: pointer to db
*/
RequestHandlerFactory::RequestHandlerFactory(IDatabase* db):
    m_database(db), m_loginManager(LoginManager(db))
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
get the loginManager
in: void
out: reference to m_loginManager
*/
LoginManager& RequestHandlerFactory::getLoginManager()
{
    return m_loginManager;
}