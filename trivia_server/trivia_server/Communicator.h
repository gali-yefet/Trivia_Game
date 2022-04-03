#pragma once
#include "IRequestHandler.h"
#include <WinSock2.h>
#include <Windows.h>
#include <map>

class Communicator
{
private:
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;

	void bindAndListen();
	void HandleNewClient(SOCKET socket);

public:
	void startHandleRequest();
};