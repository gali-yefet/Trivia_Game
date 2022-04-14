#pragma once
#include <stdio.h>
#include <vector>
#include "LoggedUser.h"
#include "IDatabase.h"


class LoginManager
{
public:
	void signup(std::string username, std::string password, std::string email);
	void login(std::string username, std::string password);
	void logout(std::string username);

private:

	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};