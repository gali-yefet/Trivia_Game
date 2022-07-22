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

typedef struct GetPlayersInRoomRequest
{
	unsigned int roomId;
}GetPlayersInRoomRequest;

typedef struct JoinRoomRequest
{
	unsigned int roomId;
}JoinRoomRequest;

typedef struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeOut;
}CreateRoomRequest;

typedef struct SubmitAnswerRequest
{
	unsigned int answerId;
	unsigned int time;
}SubmitAnswerRequest;

class JsonRequestPacketDeseializer
{
public:
	static LoginRequest deserializeLoginRequest(RequestInfo r);
	static SignupRequest deserializeSignupRequest(RequestInfo r);
	static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(RequestInfo r);
	static JoinRoomRequest deserializeJoinRoomRequest(RequestInfo r);
	static CreateRoomRequest deserializeCreateRoomRequest(RequestInfo r);
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(RequestInfo r);

private:
	static std::string extractValue(std::string& json, bool toInt = false);
};
