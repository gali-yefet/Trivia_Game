#pragma once
#include "Communicator.h"

class Server
{
private:
	Communicator m_communicator;

public:
	void run();
};