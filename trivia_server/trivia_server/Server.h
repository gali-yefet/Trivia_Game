#pragma once
#include "Communicator.h"
#include "RequestHandlerFactory.h"

class Server
{
private:
	Communicator m_communicator;

public:
	Server();
	void run();
};