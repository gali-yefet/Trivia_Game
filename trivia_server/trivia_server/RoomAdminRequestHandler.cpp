#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(int roomId, std::string username, RoomManager& roomManager, RequestHandlerFactory& handlerFactory):
    IRoomRequestHandler(roomId, username, roomManager, handlerFactory)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo r)
{
    return false; //TODO
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo r)
{
    return RequestResult(); //TODO
}
