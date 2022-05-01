#pragma once
#include <string>
#include <iostream>

class User
{
public:
	User() = default;
	User(const std::string& username, const std::string & password, const std::string& email);

	std::string getUsername();
	std::string getPassword();
	std::string getEmail();
	int getIsActive();

	void setUsername(const std::string& username);
	void setPassword(const std::string& password);
	void setEmail(const std::string& email);
	void setIsActive(const int& isActive);


private:
	std::string username;
	std::string password;
	std::string email;
	int isActive;
};