#pragma once
#include "LoginRequestHandler.h"
#include <iostream>
#include <vector>

struct LoginRequest
{
	std::string username;
	std::string password;
};

struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
};

class JsonRequestPacketDeseializer : public LoginRequestHandler
{
public:
	JsonRequestPacketDeseializer() = default;
	virtual bool isRequestRelevant(RequestInfo r);
	virtual RequestResult handleRequest(RequestInfo r);
	static LoginRequest deserializeLoginRequest(RequestInfo r);
	static SignupRequest deserializeSignupRequest(RequestInfo r);

};