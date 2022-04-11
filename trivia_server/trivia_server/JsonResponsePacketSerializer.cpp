#include "JsonResponsePacketSerializer.h"
#include "json/single_include/nlohmann/json.hpp"

#define SIGN_CODE '5'
#define LOGIN_CODE '6'
#define ERROR_CODE '7'

// for convenience
using json = nlohmann::json;

std::vector<unsigned char> JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse s)
{
	// create an empty structure (null)
	json j;

	j["status"] = s.status;

	std::string data = j.dump();  // returns the json as a string
	return serializeLogins(LOGIN_CODE, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeSignUpResponse(SignupResponse s)
{
	// create an empty structure (null)
	json j;

	j["status"] = s.status;

	std::string data = j.dump();  // returns the json as a string
	return serializeLogins(SIGN_CODE, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse s)
{
	// create an empty structure (null)
	json j;

	j["message"] = s.message;

	std::string data = j.dump();  // returns the json as a string
	return serializeLogins(ERROR_CODE, data);
}


std::vector<unsigned char> JsonResponsePacketSerializer::serializeLogins(char code, std::string data)
{
	std::string message = code + std::to_string(static_cast<int>(data.length() * sizeof(unsigned char))) + data; //make the full response as a string

	std::vector<unsigned char> bytes_buffer(message.begin(), message.end());// enter the response to a vector of bytes
	return bytes_buffer;
}