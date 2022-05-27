#include "GameRequestHandler.h"
#include "define.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

bool GameRequestHandler::isRequestRelevant(RequestInfo r)
{
	return false; //TODO
}

RequestResult GameRequestHandler::handleRequest(RequestInfo r)
{
	return RequestResult(); //TODO
}
