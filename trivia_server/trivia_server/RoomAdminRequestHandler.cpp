#include "RoomAdminRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(int roomId, std::string username, RoomManager& roomManager, RequestHandlerFactory& handlerFactory):
    m_room(roomManager.getRoom(roomId)), m_user(LoggedUser(username)), m_roomManager(roomManager), m_handlerFactory(handlerFactory) {
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo r)
{
    return r.requestCode == CLOSE_ROOM || r.requestCode == START_GAME || r.requestCode == GET_ROOM_STATE;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo r)
{
    m_room = m_roomManager.getRoom(m_room.getRoomData().id); //refresh the room

    return RequestResult(); //TODO
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo r)
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
