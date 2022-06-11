#include "Server.h"

#include <thread>
#include <iostream>

/*
initilize the db, communicator, and factory
in: none
*/
Server::Server():
	m_database(new SqliteDataBase()), m_handlerFactory(m_database), m_communicator(m_handlerFactory)
{
}

/*
start the server. create a thread that handle clients. if it gets a message with EXIT, it will shut down.
in: void
in: void
*/
void Server::run()
{
	try
	{
		//start the communicator to handle clients
		std::thread tr(&Communicator::startHandleRequest, m_communicator);
		tr.detach();
	}
	catch (const std::exception& e)
	{
		throw e;
	}
	
	//check whether to exit or not 
	std::string in;
	while (true)
	{
		std::cin >> in;
		if (in == "EXIT")
			break;
	}
}
