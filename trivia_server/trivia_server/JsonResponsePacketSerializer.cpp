#include "JsonResponsePacketSerializer.h"
#include "json/single_include/nlohmann/json.hpp"

// for convenience
using json = nlohmann::json;

std::vector<unsigned char> JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse r)
{
	// create an empty structure (null)
	json j;
	j["status"] = r.status;

	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(LOGIN_CODE, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeSignUpResponse(SignupResponse r)
{
	// create an empty structure (null)
	json j;
	j["status"] = r.status;

	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(SIGN_CODE, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse r)
{
	// create an empty structure (null)
	json j;
	j["message"] = r.message;

	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(ERROR_CODE, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeLogoutResponse(LogoutResponse r)
{
	// create an empty structure (null)
	json j;
	j["status"] = r.status;

	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(LOGOUT, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeJoinRoomResponse(JoinRoomResponse r)
{
	// create an empty structure (null)
	json j;
	j["status"] = r.status;

	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(JOIN_ROOM, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeCreateRoomResponse(CreateRoomResponse r)
{
	// create an empty structure (null)
	json j;
	j["status"] = r.status;

	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(CREATE_ROOM, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetRoomsResponse(GetRoomsResponse r)
{
	//create a vector of rooms data
	std::vector<json> rooms;
	for (auto i = r.rooms.begin(); i != r.rooms.end(); ++i)
	{
		json roomData;
		roomData["name"] = eraseQuotes(i->name);
		roomData["id"] = i->id;
		roomData["isActive"] = i->isActive;
		roomData["maxPlayers"] = i->maxPlayers;
		roomData["numOfQuestionsInGame"] = i->numOfQuestionsInGame;
		roomData["timePerQuestion"] = i->timePerQuestion;
		rooms.push_back(roomData);
	}

	json j;
	j["status"] = r.status;
	j["Rooms"] = rooms;

	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(GET_ROOMS, data);

}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetPlayersInRoomResponse(GetPlayersInRoomResponse r)
{
	//create msg
	std::string players = "";
	for (auto i = r.players.begin(); i != r.players.end(); ++i)
		players += eraseQuotes(*i) + ", ";
	players = players.substr(0, players.length() - 2);

	// create an empty structure (null)
	json j;
	j["PlayesrInRoom"] = players;

	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(GET_PLAYERS_IN_ROOM, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetHighScoreResponse(GetHighScoreResponse r)
{
	json j;
	j["status"] = r.status;
	j["statistics"] = r.statistics;
	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(GET_HIGH_SCORE, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetPersonalStatsResponse(GetPersonalStatsResponse r)
{
	json j;
	j["status"] = r.status;
	j["statistics"] = r.statistics;
	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(GET_PERSONAL_STATS, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeCloseRoomResponse(CloseRoomResponse r)
{
	json j;
	j["status"] = r.status;
	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(CLOSE_ROOM, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeStartGameResponse(StartGameResponse r)
{
	json j;
	j["status"] = r.status;
	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(START_GAME, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetRoomStateResponse(GetRoomStateResponse r)
{
	json j;
	j["status"] = r.status;
	j["hasGameBegun"] = r.hasGameBegun;
	j["isRoomClosed"] = r.isClosed;
	j["questionCount"] = r.questionCount;
	j["answerTimeout"] = r.answerTimeout;
	for (int i = 0; i < r.players.size(); i++)
		r.players[i] = eraseQuotes(r.players[i]);
	j["players"] = r.players;

	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(GET_ROOM_STATE, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeLeaveRoomResponse(LeaveRoomResponse r)
{
	json j;
	j["status"] = r.status;
	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(LEAVE_ROOM, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeLeaveGameResponse(LeaveGameResponse r)
{
	json j;
	j["status"] = r.status;
	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(LEAVE_GAME, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetQuestionResponse(GetQuestionResponse r, bool gameOver)
{
	json j;
	j["status"] = !gameOver ? r.status : ERROR_CODE;
	j["answers"] = !gameOver ? r.answers : std::map<unsigned int, std::string>();
	j["question"] = !gameOver ? r.question : "";
	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(GET_QUESTION, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeSubmitAnswerResponse(SubmitAnswerResponse r)
{
	json j;
	j["status"] = r.status;
	j["correctAnswerId"] = r.correctAnswerId;
	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(SUBMIT_ANSWER, data);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetGameResultsResponse(GetGameResultsResponse r, bool gameOver)
{
	json j;
	j["status"] = gameOver ? r.status : ERROR_CODE;

	//create a vector of results response
	std::vector<json> results;
	if (gameOver)
	{
		for (auto i = r.results.begin(); i != r.results.end(); ++i)
		{
			json result;
			result["averageAnserTime"] = i->averageAnserTime;
			result["correctAnswerCount"] = i->correctAnswerCount;
			result["username"] = eraseQuotes(i->username);
			result["wrongAnswerCount"] = i->wrongAnswerCount;
			results.push_back(result);
		}
	}
	j["results"] = results;
	
	std::string data = j.dump();  // returns the json as a string
	return serializeMsg(GET_GAME_RESULTS, data);
}

/*
serialize a response msg
in: code, and data
out: the serialized msg
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeMsg(int code, std::string data)
{
	std::string codeStr = std::to_string(code);
	while (codeStr.length() < 2)
		codeStr = " " + codeStr;
	std::string bytes = std::to_string(static_cast<int>(data.length() * sizeof(unsigned char)));
	while (bytes.length() < 4)
		bytes = " " + bytes;
	std::string message = codeStr + bytes + data;
	std::vector<unsigned char> bytes_buffer(message.begin(), message.end());// enter the response to a vector of bytes
	return bytes_buffer;
}

std::string JsonResponsePacketSerializer::eraseQuotes(std::string data)
{
	return data.substr(1, data.length() - 2);
}
