#include "MenuRequestHandler.h"
#include "define.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser user, RoomManager& roomManger, StatisticsManager& statisticsManager, RequestHandlerFactory& handlerFactory):
	m_user(user), m_roomManger(roomManger), m_statisticsManager(statisticsManager), m_handlerFactory(handlerFactory)
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo r)
{
	return r.requestCode == CREATE_ROOM || 
		r.requestCode == GET_ROOMS || 
		r.requestCode == GET_PLAYERS_IN_ROOM || 
		r.requestCode == JOIN_ROOM || 
		r.requestCode == GET_HIGH_SCORE ||
		r.requestCode == GET_PERSONAL_STATS ||
		r.requestCode == LOGOUT;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo r)
{
	RequestResult result;
	switch (r.requestCode)
	{
	case CREATE_ROOM:
		result = createRoom(r);
		break;
	case GET_ROOMS:
		result = getRooms(r);
		break;
	case GET_PLAYERS_IN_ROOM:
		result = getPlayesrInRoom(r);
		break;
	case JOIN_ROOM:
		result = joinRoom(r);
		break;
	case GET_PERSONAL_STATS:
		result = getPersonalStats(r);
		break;
	case GET_HIGH_SCORE:
		result = getHighScore(r);
		break;
	case LOGOUT:
		result = signout(r);
		break;
	default:
		break;
	}
	return result;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo r)
{
	GetRoomsResponse response;
	response.status = GET_ROOMS;
	response.rooms = m_roomManger.getRooms();
	std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeGetRoomsResponse(response);
	return IRequestHandler::createRequestResult(buffer, this);
}

RequestResult MenuRequestHandler::getPlayesrInRoom(RequestInfo r)
{
	GetPlayersInRoomRequest request = JsonRequestPacketDeseializer::deserializeGetPlayersInRoomRequest(r);
	GetPlayersInRoomResponse response;
	response.players = m_roomManger.getRoom(request.roomId).getAllUsers();
	std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeGetPlayersInRoomResponse(response);
	return IRequestHandler::createRequestResult(buffer, this);
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo r)
{
	JoinRoomRequest request = JsonRequestPacketDeseializer::deserializeJoinRoomRequest(r);
	m_roomManger.joinRoom(request.roomId, m_user);

	JoinRoomResponse response;
	response.status = JOIN_ROOM;
	std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeJoinRoomResponse(response);
	return IRequestHandler::createRequestResult(buffer, m_handlerFactory.createRoomMemberRequestHandler(request.roomId, m_user.getUsername()));
}

RequestResult MenuRequestHandler::createRoom(RequestInfo r)
{
	CreateRoomRequest request = JsonRequestPacketDeseializer::deserializeCreateRoomRequest(r);
	RoomData roomData;
	roomData.maxPlayers = request.maxUsers;
	roomData.name = request.roomName;
	roomData.numOfQuestionsInGame = request.questionCount;
	roomData.timePerQuestion = request.answerTimeOut;
	roomData.id = m_roomManger.createRoomId();
	roomData.isActive = 1;

	m_roomManger.createRoom(m_user, roomData);

	CreateRoomResponse response;
	response.status = CREATE_ROOM;
	std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeCreateRoomResponse(response);
	return IRequestHandler::createRequestResult(buffer, m_handlerFactory.createRoomAdminRequestHandler(roomData.id, m_user.getUsername()));
}

RequestResult MenuRequestHandler::signout(RequestInfo r)
{
	m_handlerFactory.getDatabase()->logout(m_user.getUsername());
	LogoutResponse response;
	response.status = LOGOUT;
	std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeLogoutResponse(response);
	return IRequestHandler::createRequestResult(buffer, nullptr);
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo r)
{
	GetPersonalStatsResponse response;
	response.status = GET_PERSONAL_STATS;
	response.statistics = m_statisticsManager.getUserStatistics(m_user.getUsername());
	std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeGetPersonalStatsResponse(response);
	return IRequestHandler::createRequestResult(buffer, this);
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo r)
{
	GetHighScoreResponse response;
	response.status = GET_HIGH_SCORE;
	response.statistics = m_statisticsManager.getHighScore();
	std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeGetHighScoreResponse(response);
	return IRequestHandler::createRequestResult(buffer, this);
}
