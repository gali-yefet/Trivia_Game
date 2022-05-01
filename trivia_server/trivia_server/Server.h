#pragma once
#include "Communicator.h"
#include "RequestHandlerFactory.h"
#include "SqliteDataBase.h"

class Server
{
private:
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;
	Communicator m_communicator;


public:
	Server();
	void run();
};