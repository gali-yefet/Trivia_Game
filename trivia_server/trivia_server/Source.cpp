#include "Server.h"
#include "WSAInitializer.h"
#include "SqliteDataBase.h"
#include <exception>
#include <iostream>

int main()
{
	SqliteDataBase db;
	db.open();
	try
	{
		TRACE("Starting...");
		WSAInitializer wsa_init;
		Server md_server;

		md_server.run();
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was thrown in function: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown exception in main !" << std::endl;
	}
	return 0;
}