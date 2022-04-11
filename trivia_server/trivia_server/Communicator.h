<<<<<<< HEAD
#pragma comment (lib, "ws2_32.lib")
=======
#pragma once
>>>>>>> 5060f6ee31128b8355c8d61e7e55d48b17568996
#include "IRequestHandler.h"
#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include <iostream>

#define PORT 3086

#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);

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
<<<<<<< HEAD
	std::string getData(const SOCKET sc, const int bytesNum, const int flags = 0);
};
=======
	std::string getData(const SOCKET sc, const int bytesNum, const int flags=0);
};
>>>>>>> 5060f6ee31128b8355c8d61e7e55d48b17568996
