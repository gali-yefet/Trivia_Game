#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string username)
	:m_username(username)
{}

std::string LoggedUser::getUsername()
{
	return this->m_username;
}

bool operator<(const LoggedUser& user1, const LoggedUser& user2)
{
	return user1.m_username > user2.m_username;
}
