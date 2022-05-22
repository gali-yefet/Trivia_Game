#include "RoomMemberRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "GameRequestHandler.h"

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
    int roomStatus = m_room.getRoomData().isActive;
    if (roomStatus == CLOSED)
    {
        CloseRoomResponse response;
        response.status = r.requestCode;
        std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeCloseRoomResponse(response);
        return IRequestHandler::createRequestResult(buffer, m_handlerFactory.createMenuRequestHandler(m_user.getUsername()));
    }
    else if (roomStatus == IN_GAME)
    {
        StartGameResponse response;
        response.status = r.requestCode;
        std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeStartGameResponse(response);
        return IRequestHandler::createRequestResult(buffer, new GameRequestHandler); //TODO: change to function that creates room
    }
    RequestResult result;
    switch (r.requestCode)
    {
    case LEAVE_ROOM:
        result = leaveRoom(r);
        break;
    case GET_ROOM_STATE:
        result = getRoomState(r);
        break;
    }
    return result;
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
