#pragma comment (lib, "ws2_32.lib")

#include "Server.h"
#include "WSAInitializer.h"
#include <exception>
#include <iostream>

int main()
{
	WSAInitializer wsa_init;
	return 0;
}