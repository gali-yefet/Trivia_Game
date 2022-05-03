#include "MenuRequestHandler.h"
#include "define.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser user, RoomManager& roomManger, RequestHandlerFactory& handlerFactory):
	m_user(user), m_roomManger(roomManger), m_handlerFactory(handlerFactory)
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo r)
{
	return r.requestCode == CREATE_ROOM || 
		r.requestCode == GET_ROOMS || 
		r.requestCode == GET_PLAYERS_IN_ROOM || 
		r.requestCode == JOIN_ROOM || 
		r.requestCode == GET_STATISTICS ||
		r.requestCode == LOGOUT;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo r)
{
    return RequestResult(); //TODO
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
	return IRequestHandler::createRequestResult(buffer, new RoomMemberRequestHandler); //TODO: change to creating a RoomMemberRequestHandler with the factory method
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
	return IRequestHandler::createRequestResult(buffer, new RoomAdminRequestHandler); //TODO: change to creating a RoomAdminRequestHandler with the factory method}
}