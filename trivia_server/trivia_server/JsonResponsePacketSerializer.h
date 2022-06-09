#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include "define.h"
#include "Room.h"

typedef struct PlayerResults
{
	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnserTime;
}PlayerResults;

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

typedef struct CloseRoomResponse
{
	unsigned int status;
}CloseRoomResponse;

typedef struct StartGameResponse
{
	unsigned int status;
}StartGameResponse;

typedef struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
	bool isClosed;
}GetRoomStateResponse;

typedef struct LeaveRoomResponse
{
	unsigned int status;
}LeaveRoomResponse;

typedef struct LeaveGameResponse 
{
	unsigned int status;
}LeaveGameResponse;

typedef struct GetQuestionResponse
{
	unsigned int status;
	std::string question;
	std::map<unsigned int, std::string> answers;
}GetQuestionResponse;

typedef struct SubmitAnswerResponse
{
	unsigned int status;
	unsigned int correctAnswerId;
}SubmitAnswerResponse;

typedef struct GetGameResultsResponse
{
	unsigned int status;
	std::vector<PlayerResults> results;
}GetGameResultsResponse;


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
	static std::vector<unsigned char> serializeCloseRoomResponse(CloseRoomResponse r);
	static std::vector<unsigned char> serializeStartGameResponse(StartGameResponse r);
	static std::vector<unsigned char> serializeGetRoomStateResponse(GetRoomStateResponse r);
	static std::vector<unsigned char> serializeLeaveRoomResponse(LeaveRoomResponse r);
	static std::vector<unsigned char> serializeLeaveGameResponse(LeaveGameResponse r);
	static std::vector<unsigned char> serializeGetQuestionResponse(GetQuestionResponse r, bool gameOver);
	static std::vector<unsigned char> serializeSubmitAnswerResponse(SubmitAnswerResponse r);
	static std::vector<unsigned char> serializeGetGameResultsResponse(GetGameResultsResponse r, bool gameOver);
	
private:
	static std::vector<unsigned char> serializeMsg(int code, std::string data);
	static std::string eraseQuotes(std::string data);

};
