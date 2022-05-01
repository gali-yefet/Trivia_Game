#pragma once
#include "LoginRequestHandler.h"
#include <iostream>
#include <vector>

typedef struct LoginRequest
{
	std::string username;
	std::string password;
}LoginRequest;

typedef struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
}SignupRequest;

class JsonRequestPacketDeseializer
{
public:
	static LoginRequest deserializeLoginRequest(RequestInfo r);
	static SignupRequest deserializeSignupRequest(RequestInfo r);

private:
	static std::string eraseQuotes(std::string str);
};