#pragma once
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler();
	virtual bool isRequestRelevant(RequestInfo r);
	virtual RequestResult handleRequest(RequestInfo r);
	static RequestResult login(RequestInfo);
	static RequestResult signup(RequestInfo);

private:
	//LoginManager& m_loginManager;
	//RequestHandlerFactory& m_handlerFactory;
};
