#include "RoomMemberRequestHandler.h"

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
    return RequestResult(); //TODO
}
