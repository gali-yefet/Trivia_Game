#include "LoginManager.h"

void LoginManager::signup(std::string username, std::string password, std::string email)
{
	this->m_database->addNewUser(username, password, email);
}

void LoginManager::login(std::string username, std::string password)
{
	if (this->m_database->doesUserExist(username) && this->m_database->doesPasswordMatch(username, password))
	{
		this->m_loggedUsers.push_back(LoggedUser(username));
	}
}

void LoginManager::logout(std::string username)
{
	for (auto it = this->m_loggedUsers.begin(); it != this->m_loggedUsers.end(); it++) 
	{
		if ((*it).getUsername() == username)
		{
			this->m_loggedUsers.erase(it);
			break;
		}
	}
}
