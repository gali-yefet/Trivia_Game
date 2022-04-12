#include "JsonResponsePacketSerializer.h"
#include "json/single_include/nlohmann/json.hpp"

// for convenience
using json = nlohmann::json;

std::vector<unsigned char> JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse s)
{
	// create an empty structure (null)
	json j;

	j["status"] = s.status;

	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(LOGIN_CODE, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeSignUpResponse(SignupResponse s)
{
	// create an empty structure (null)
	json j;

	j["status"] = s.status;

	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(SIGN_CODE, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse s)
{
	// create an empty structure (null)
	json j;

	j["message"] = s.message;

	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(ERROR_CODE, data);
}

/*
serialize a response msg
in: code, and data
out: the serialized msg
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeMsg(int code, std::string data)
{
	std::string message = std::to_string(code) + std::to_string(static_cast<int>(data.length() * sizeof(unsigned char))) + data; //make the full response as a string

	std::vector<unsigned char> bytes_buffer(message.begin(), message.end());// enter the response to a vector of bytes
	return bytes_buffer;
}
