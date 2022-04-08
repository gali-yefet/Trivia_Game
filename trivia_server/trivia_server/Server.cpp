#include "Server.h"

#include <thread>

/*
initilize the m_communicator with a communicator.
in: none
*/
Server::Server():
	m_communicator(Communicator())
{
}

/*
start the server. create a thread that handle clients. if it gets a message with EXIT, it will shut down.
in: void
in: void
*/
void Server::run()
{
	//start the communicator to handle clients
	std::thread tr(&Communicator::startHandleRequest, m_communicator);
	tr.detach();

	//check whether to exit or not 
	while (true)
	{
		std::string in;
		std::cin >> in;
		if (in == "EXIT")
			break;
	}
}
