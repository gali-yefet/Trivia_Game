#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>

typedef struct LoginResponse
{
	unsigned int status;
}LoginResponse;

typedef struct SignupResponse
{
	unsigned int status;
}SignupResponse;

typedef struct ErrorResponse
{
	std::string message;
}ErrorResponse;

class JsonResponsePacketSerializer
{
public:
	static std::vector<unsigned char> serializeLoginResponse(LoginResponse s);
	static std::vector<unsigned char> serializeSignUpResponse(SignupResponse s);
	static std::vector<unsigned char> serializeErrorResponse(ErrorResponse s);

private:
	static std::vector<unsigned char> serializeLogins(char code, std::string data);

};