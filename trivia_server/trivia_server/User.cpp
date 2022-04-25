#include "User.h"

User::User(const std::string& username, const std::string& password, const std::string& email)
	:username(username), password(password), email(email)

{}

std::string User::getUsername()
{
	return this->username;
}

std::string User::getPassword()
{
	return this->password;
}

std::string User::getEmail()
{
	return this->email;
}

void User::setUsername(const std::string& username)
{
	this->username = username;
}

void User::setPassword(const std::string& password)
{
	this->password = password;
}

void User::setEmail(const std::string& email)
{
	this->email = email;
}
