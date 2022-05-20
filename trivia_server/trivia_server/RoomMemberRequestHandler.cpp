#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(int roomId, std::string username, RoomManager& roomManager, RequestHandlerFactory& handlerFactory):
    IRoomRequestHandler(roomId, username, roomManager, handlerFactory)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo r)
{
    return false; //TODO
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo r)
{
    return RequestResult(); //TODO
}
