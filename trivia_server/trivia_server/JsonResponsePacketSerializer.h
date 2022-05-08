#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include "define.h"
#include "Room.h"

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

typedef struct LogoutResponse
{
	unsigned int status;
}LogoutResponse;

typedef struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
}GetRoomsResponse;

typedef struct GetPlayersInRoomResponse
{
	std::vector<std::string> players;
}GetPlayersInRoomResponse;

typedef struct GetHighScoreResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
}GetHighScoreResponse;

typedef struct GetPersonalStatsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
}GetPersonalStatsResponse;

typedef struct JoinRoomResponse
{
	unsigned int status;

}JoinRoomResponse;

typedef struct CreateRoomResponse
{
	unsigned int status;
}CreateRoomResponse;


class JsonResponsePacketSerializer
{
public:
	static std::vector<unsigned char> serializeLoginResponse(LoginResponse r);
	static std::vector<unsigned char> serializeSignUpResponse(SignupResponse r);
	static std::vector<unsigned char> serializeErrorResponse(ErrorResponse r);
	static std::vector<unsigned char> serializeLogoutResponse(LogoutResponse r);
	static std::vector<unsigned char> serializeJoinRoomResponse(JoinRoomResponse r);
	static std::vector<unsigned char> serializeCreateRoomResponse(CreateRoomResponse r);
	static std::vector<unsigned char> serializeGetRoomsResponse(GetRoomsResponse r);
	static std::vector<unsigned char> serializeGetPlayersInRoomResponse(GetPlayersInRoomResponse r);
	static std::vector<unsigned char> serializeGetHighScoreResponse(GetHighScoreResponse r);
	static std::vector<unsigned char> serializeGetPersonalStatsResponse(GetPersonalStatsResponse r);
	

private:
	static std::vector<unsigned char> serializeMsg(int code, std::string data);
	static std::string eraseQuotes(std::string data);

};