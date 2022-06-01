#pragma comment (lib, "ws2_32.lib")
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "define.h"

#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include <iostream>

class Communicator
{
public:
	Communicator(RequestHandlerFactory& handlerFactory);
	~Communicator();

	void startHandleRequest();
	void bindAndListen();

private:
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;

	void HandleNewClient(SOCKET socket);

	void closeClient(std::string username, int roomId, bool isAdmin);
	void setCurrUsername(RequestInfo r, std::string& username);
	void setCurrRoomId(RequestInfo r, int& roomId);
	void setIsAdmin(RequestInfo r, bool& isAdmin);

	bool checkIfSocketIsOpen(SOCKET socket);
	void sendData(const SOCKET sc, const std::string message);
	std::string getData(const SOCKET sc, const int bytesNum, const int flags = 0);
};
