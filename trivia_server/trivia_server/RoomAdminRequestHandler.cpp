#include "RoomAdminRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "GameRequestHandler.h"
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
    case CLOSE_ROOM:
        result = closeRoom(r);
        break;
    case START_GAME:
        result = startGame(r);
        break;
    case GET_ROOM_STATE:
        result = getRoomState(r);
        break;
    }
    return result;
}


RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo r)
{
    //remove all users from room
    std::vector <std::string> users =  m_room.getAllUsers();
    for (int i = 0; i < users.size(); i++) 
    {
        m_room.removeUser(LoggedUser(users[i]));
    }
    //close the room
    m_roomManager.changeRoomState(m_room.getRoomData().id, CLOSED);

    //send response
    CloseRoomResponse response;
    response.status = r.requestCode;
    std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeCloseRoomResponse(response);
    return IRequestHandler::createRequestResult(buffer, m_handlerFactory.createMenuRequestHandler(m_user.getUsername()));
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo r)
{
    m_roomManager.changeRoomState(m_room.getRoomData().id, IN_GAME);//change the roomState to IN_GAME state
    StartGameResponse response;
    response.status = r.requestCode;
    std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeStartGameResponse(response);
    return IRequestHandler::createRequestResult(buffer, this); //TODO: create room
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
