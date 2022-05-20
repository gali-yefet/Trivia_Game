#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(int roomId, std::string username, RoomManager& roomManager, RequestHandlerFactory& handlerFactory):
    m_room(roomManager.getRoom(roomId)), m_user(LoggedUser(username)), m_roomManager(roomManager), m_handlerFactory(handlerFactory) {
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo r)
{
    return r.requestCode == CLOSE_ROOM || r.requestCode == START_GAME || r.requestCode == GET_ROOM_STATE;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo r)
{
    return RequestResult(); //TODO
}
