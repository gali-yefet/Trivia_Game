#include "MenuRequestHandler.h"
#include "define.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

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