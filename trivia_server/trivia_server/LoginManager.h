#pragma once
#include <stdio.h>
#include <vector>
#include "LoggedUser.h"
#include "IDatabase.h"


class LoginManager
{
public:
	LoginManager(IDatabase* db);
	bool signup(std::string username, std::string password, std::string email);
	bool login(std::string username, std::string password);
	bool logout(std::string username);

private:

	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};
