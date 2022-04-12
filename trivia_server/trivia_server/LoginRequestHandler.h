#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "define.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory);
	virtual bool isRequestRelevant(RequestInfo r);
	virtual RequestResult handleRequest(RequestInfo r);

private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult login(RequestInfo r);
	RequestResult signup(RequestInfo r);
};