#include "JsonResponsePacketSerializer.h"
#include "json/single_include/nlohmann/json.hpp"

#define SIGN_CODE '5'
#define LOGIN_CODE '6'
#define ERROR_CODE '7'

// for convenience
using json = nlohmann::json;

std::vector<unsigned char> JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse s)
{
	return serializeLogins(LOGIN_CODE, "status", s);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeSignUpResponse(SignupResponse s)
{
	return serializeLogins(SIGN_CODE, "status", s);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse s)
{
	return serializeLogins(ERROR_CODE, "message", s);
}

template <class T>
std::vector<unsigned char> JsonResponsePacketSerializer::serializeLogins(int code, std::string atr, T response)
{
	// create an empty structure (null)
	json j;

	//add status key into the json
	j[atr] = T.atr;

	std::string data = j.dump();  // returns the json as a string

	std::string message = code + std::to_string(static_cast<int>(data.length() * 2)) + data; //make the full response as a string

	std::vector<unsigned char> bytes_buffer(message.begin(), message.end());// enter the response to a vector of bytes
	return bytes_buffer;
}