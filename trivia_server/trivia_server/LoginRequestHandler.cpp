#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo r)
{
	return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo r)
{
	return RequestResult();
}

RequestResult LoginRequestHandler::login(RequestInfo)
{
	return RequestResult();
}

RequestResult LoginRequestHandler::signup(RequestInfo)
{
	return RequestResult();
}

