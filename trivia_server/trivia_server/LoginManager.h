#pragma once
#include <iostream>

class LoginManager
{
public:
	bool signup(std::string username, std::string password, std::string email);
	bool login(std::string username, std::string password);
};

