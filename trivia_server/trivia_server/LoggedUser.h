#pragma once
#include <iostream>

class LoggedUser
{
public:
	LoggedUser(std::string username);
	std::string getUsername();
	friend bool operator<(const LoggedUser& user1, const LoggedUser& user2);

private:
	std::string m_username;

};