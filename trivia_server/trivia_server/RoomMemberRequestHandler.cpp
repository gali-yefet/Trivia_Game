#include "RoomMemberRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(int roomId, std::string username, RoomManager& roomManager, RequestHandlerFactory& handlerFactory):
    m_room(roomManager.getRoom(roomId)), m_user(LoggedUser(username)), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo r)
{
    return r.requestCode == LEAVE_ROOM || r.requestCode == GET_ROOM_STATE;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo r)
{
    m_room = m_roomManager.getRoom(m_room.getRoomData().id); //refresh the room

    return RequestResult(); //TODO
}


RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo r)
{
    LeaveRoomResponse response;
    response.status = r.requestCode;
    std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeLeaveRoomResponse(response);
    return IRequestHandler::createRequestResult(buffer, m_handlerFactory.createMenuRequestHandler(m_user.getUsername()));
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo r)
{
    GetRoomStateResponse response;
    response.answerTimeout = m_room.getRoomData().timePerQuestion;
    response.hasGameBegun = m_room.getRoomData().isActive == IN_GAME;
    response.players = m_room.getAllUsers();
    response.questionCount = m_room.getRoomData().numOfQuestionsInGame;
    response.status = r.requestCode;
    std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeGetRoomStateResponse(response);
    return IRequestHandler::createRequestResult(buffer, this);
}
