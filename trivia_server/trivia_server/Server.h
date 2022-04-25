#pragma once
#include "Communicator.h"
#include "RequestHandlerFactory.h"
#include "SqliteDataBase.h"

class Server
{
private:
	Communicator m_communicator;
	RequestHandlerFactory m_handlerFactory;
	IDatabase* m_database;


public:
	Server();
	void run();
};