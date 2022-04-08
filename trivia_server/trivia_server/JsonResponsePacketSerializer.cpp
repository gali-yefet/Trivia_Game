#include "JsonResponsePacketSerializer.h"
#include "json/include/nlohmann/json.hpp"

#define CODE '6'

// for convenience
using json = nlohmann::json_pointer;

std::vector<unsigned char> JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse s)
{
	// create an empty structure (null)
	json j;

	//add status key into the json
	j["status"] = s.status;

	std::string data = j.dump();  // returns the json as a string

	std::string message = CODE + std::to_string(static_cast<int>(data.length() * 2)) + data; //make the full response as a string

	std::vector<unsigned char> bytes_buffer(message.begin(), message.end());// enter the response to a vector of bytes
	return bytes_buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeSignUpResponse(SignupResponse s)
{
	// create an empty structure (null)
	json j;

	//add status key into the json
	j["status"] = s.status;

	std::string data = j.dump();  // returns the json as a string

	std::string message = CODE + std::to_string(static_cast<int>(data.length() * 2)) + data; //make the full response as a string

	std::vector<unsigned char> bytes_buffer(message.begin(), message.end());// enter the response to a vector of bytes
	return bytes_buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse s)
{
	// create an empty structure (null)
	json j;

	//add status key into the json
	j["message"] = s.message;

	std::string data = j.dump();  // returns the json as a string

	std::string message = CODE + std::to_string(static_cast<int>(data.length() * 2)) + data; //make the full response as a string

	std::vector<unsigned char> bytes_buffer(message.begin(), message.end());// enter the response to a vector of bytes
	return bytes_buffer;
}
