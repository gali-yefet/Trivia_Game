#include "Communicator.h"
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include <exception>
#include <thread>
#include <string>


/*
create the server socket
in: void
*/
Communicator::Communicator(RequestHandlerFactory& handlerFactory):
	m_handlerFactory(handlerFactory)
{
	// this server use TCP. that's why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

/*
close server socket
*/
Communicator::~Communicator()
{
	TRACE(__FUNCTION__ " closing accepting socket");
	closesocket(m_serverSocket);
}


/*
start handling clients. create a new socket and thread for each client
in: void
out: void
*/
void Communicator::startHandleRequest()
{
	bindAndListen();
	
	//accept clients
	while (true)
	{
		//create socket
		SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);
	
		// create new thread for client	and detach from it
		std::thread tr(&Communicator::HandleNewClient, this, client_socket);
		tr.detach();
	
		//insert the client to the clients map
		LoginRequestHandler* handler = m_handlerFactory.createLoginRequestHandler();
		m_clients.insert(std::pair<SOCKET, IRequestHandler*>(client_socket, handler));
		TRACE("Client accepted !");
	}
}

/*
bind the server socket and listen on it from clients
in: void
out: void
*/
void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;

	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	TRACE("binded");
	
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	TRACE("listening...");
}

/*
communicate with the client
in: client socket
out: void
*/
void Communicator::HandleNewClient(SOCKET socket)
{	
	RequestInfo r;
	std::string currUsername = "";
	int currRoomId = NOT_IN_ROOM;
	bool isAdmin = false;
	while(checkIfSocketIsOpen(socket))
	{
		//get the msg into the struct
		r.receivalTime = time(&r.receivalTime);
		try
		{
			std::string code = getData(socket, 2);
			r.requestCode = std::stoi(code);//get the code

			std::string len = getData(socket, 4);
			int bytes = std::stoi(len);// get the json size

			std::string msg = getData(socket, bytes); // get the json
			r.json = std::vector<unsigned char>(msg.begin(), msg.end());
		}
		catch (const std::exception& e)
		{
			continue;
		}

		//set the right data about the user
		setCurrUsername(r, currUsername);
		setCurrRoomId(r, currRoomId);
		setIsAdmin(r, isAdmin);

		//handle the client request according to socket
		auto it = m_clients.find(socket);
		if (it == m_clients.end())
		{
			std::cout << "socket not found";
		}
		else
		{
			IRequestHandler* handler = it->second;
			if (handler != nullptr && handler->isRequestRelevant(r))
			{
				m_clients.erase(socket);
				RequestResult res = handler->handleRequest(r);
				m_clients.insert(std::pair<SOCKET, IRequestHandler*>(socket, res.newHandler));
				sendData(socket, res.buffer);
			}
		}
	}
	closeClient(currUsername, currRoomId, isAdmin);
}

void Communicator::closeClient(std::string username, int roomId, bool isAdmin)
{
	//close all things
	if (roomId != NOT_IN_ROOM)
	{
		if (isAdmin)
			m_handlerFactory.createRoomAdminRequestHandler(roomId, username)->closeRoom();
		else
			m_handlerFactory.createRoomMemberRequestHandler(roomId, username)->leaveRoom();
	}

	//logout
	if (username != "")
		m_handlerFactory.getDatabase()->logout(username);
}

void Communicator::setCurrUsername(RequestInfo r, std::string& username)
{
	switch (r.requestCode)
	{
	case LOGIN_CODE:
		username = JsonRequestPacketDeseializer::deserializeLoginRequest(r).username;
		break;
	case SIGN_CODE:
		username = JsonRequestPacketDeseializer::deserializeSignupRequest(r).username;
		break;
	case LOGOUT:
		username = "";
	}
}

void Communicator::setCurrRoomId(RequestInfo r, int& roomId)
{
	switch (r.requestCode)
	{
	case CREATE_ROOM:
		roomId = m_handlerFactory.getRoomManager().getRoomId(JsonRequestPacketDeseializer::deserializeCreateRoomRequest(r).roomName);
		break;
	case JOIN_ROOM:
		roomId = JsonRequestPacketDeseializer::deserializeJoinRoomRequest(r).roomId;
		break;
	case LEAVE_ROOM:
	case CLOSE_ROOM:
		roomId = NOT_IN_ROOM;
		break;
	}
}

void Communicator::setIsAdmin(RequestInfo r, bool& isAdmin)
{
	switch (r.requestCode)
	{
	case CREATE_ROOM:
		isAdmin = true;
		break;
	case CLOSE_ROOM:
		isAdmin = false;
		break;
	}
}

bool Communicator::checkIfSocketIsOpen(SOCKET socket)
{
	char* data = new char[1];
	int res = recv(socket, data, 0, NULL);
	return res != INVALID_SOCKET;
}

/*
send msg to client
in: client socket, message to send
in: void
*/
void Communicator::sendData(const SOCKET sc, const std::string message)
{
	const char* data = message.c_str();
	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
		throw std::exception("Error while sending message to client");
}

/*
get data from client socket
in: client socket, size of data, flags(optional)
out: message from the client
*/
std::string Communicator::getData(const SOCKET sc, const int bytesNum, const int flags)
{
	if (bytesNum == 0)
	{
		return "";
	}

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, flags);
	if (res == INVALID_SOCKET || res!= bytesNum)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}
	data[bytesNum] = 0;
	std::string received(data);
	delete[] data;
	return received;
}