#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>

struct LoginResponse
{
	unsigned int status;
};

struct SignupResponse
{
	unsigned int status;
};

struct ErrorResponse
{
	std::string message;
};

class JsonResponsePacketSerializer
{
public:
	static std::vector<unsigned char> serializeLoginResponse(LoginResponse s);
	static std::vector<unsigned char> serializeSignUpResponse(SignupResponse s);
	static std::vector<unsigned char> serializeErrorResponse(ErrorResponse s);

private:
	template <class T>
	static std::vector<unsigned char> serializeLogins(int code, std::string atr, T response);

};