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

	void setUsername(const std::string& username);
	void setPassword(const std::string& password);
	void setEmail(const std::string& email);


private:
	std::string username;
	std::string password;
	std::string email;
};