#include "Communicator.h"
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include <exception>
#include <thread>
#include <string>

static const unsigned int IFACE = 0;

/*
create the server socket
in: void
*/
Communicator::Communicator()
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
	// why is this try necessarily ?
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		::closesocket(m_serverSocket);
	}
	catch (...) {}
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
		LoginRequestHandler* handler = new LoginRequestHandler();
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
	// again stepping out to the global namespace
	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	TRACE("binded");

	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	TRACE("listening...");
}

/*
communicate with the client (right now - send hello, and get hello back)
in: client socket
out: void
*/
void Communicator::HandleNewClient(SOCKET socket)
{
	try
	{
		RequestInfo r;
		r.receivalTime = time(&r.receivalTime);
		std::string msg = getData(socket, 1); // get the message code
		r.requestCode = std::stoi(msg);
		msg = getData(socket, 4);// get the json size
		int bytes = std::stoi(msg);
		msg = getData(socket, bytes); // get the json
		r.json = std::vector<unsigned char>(msg.begin(), msg.end());
		JsonRequestPacketDeseializer j;
		RequestResult res = j.handleRequest(r);
		sendData(socket, res.buffer);
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was thrown in function: " << e.what() << std::endl;
	}
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
	if (res == INVALID_SOCKET)
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

