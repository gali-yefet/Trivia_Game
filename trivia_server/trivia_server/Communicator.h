#pragma once
#include "IRequestHandler.h"
#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include <iostream>

#define PORT 3086

class Communicator
{
public:
	Communicator();
	~Communicator();
	void startHandleRequest();

private:
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;

	void bindAndListen();
	void HandleNewClient(SOCKET socket);
	void sendData(const SOCKET sc, const std::string message);
	std::string getData(const SOCKET sc, const int bytesNum, const int flags=0);
};