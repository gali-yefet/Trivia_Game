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
	static std::vector<unsigned char> serializeLoginResponse(struct LoginResponse s);
	static std::vector<unsigned char> serializeSignUpResponse(struct SignupResponse s);
	static std::vector<unsigned char> serializeErrorResponse(struct ErrorResponse s);

};