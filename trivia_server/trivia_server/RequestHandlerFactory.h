#pragma once
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "LoginManager.h"

class LoginRequestHandler; //Circular reference

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* db);
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();

private:
	LoginManager m_loginManager;
	IDatabase* m_database;
};

