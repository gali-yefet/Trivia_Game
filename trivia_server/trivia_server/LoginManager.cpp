#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* db):
	m_database(db)
{
}

bool LoginManager::signup(std::string username, std::string password, std::string email)
{
	if (this->m_database->doesUserExist(username))
		return false;
	this->m_database->addNewUser(username, password, email);
	return true;
}

bool LoginManager::login(std::string username, std::string password)
{
	if (this->m_database->doesUserExist(username) && this->m_database->doesPasswordMatch(username, password))
	{
		this->m_loggedUsers.push_back(LoggedUser(username));
		return true;
	}
	return false;
}

bool LoginManager::logout(std::string username)
{
	for (auto it = this->m_loggedUsers.begin(); it != this->m_loggedUsers.end(); it++)
	{
		if ((*it).getUsername() == username)
		{
			this->m_loggedUsers.erase(it);
			return true;
		}
	}
	return false;
}
