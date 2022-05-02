#include "LoginRequestHandler.h"

#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "MenuRequestHandler.h"

/*
create a new LoginRequestHandler according to login manager and handler factory
in" login manager and handler factory
*/
LoginRequestHandler::LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory):
	m_loginManager(loginManager), m_handlerFactory(handlerFactory)
{
}

/*
check if the the request is relevant for the LoginRequestHandler
in: request
out: relevant(true) or not (false)
*/
bool LoginRequestHandler::isRequestRelevant(RequestInfo r)
{
	return r.requestCode == LOGIN_CODE || r.requestCode == SIGN_CODE;
}

/*
handle the request (send to the right method)
in: request info
out: request result
*/
RequestResult LoginRequestHandler::handleRequest(RequestInfo r)
{
	RequestResult result;

	if (isRequestRelevant(r))
		result = (r.requestCode == LOGIN_CODE) ? login(r) : signup(r);
	
	return result;
}

/*
analys the request and login
in: request info
out: login respons. if faild - error response
*/
RequestResult LoginRequestHandler::login(RequestInfo r)
{
	RequestResult result;
	std::vector<unsigned char> buffer;
	LoginRequest request = JsonRequestPacketDeseializer::deserializeLoginRequest(r);
	bool worked = m_loginManager.login(request.username, request.password);
	if (worked)
	{
		//create buffer
		LoginResponse res;
		res.status = LOGIN_CODE;
		buffer = JsonResponsePacketSerializer::serializeLoginResponse(res);
	
		//create handler
		result.newHandler = m_handlerFactory.createMenuRequestHandler(request.username);
	}
	else
	{
		//create buffer
		ErrorResponse res;
		res.message = "Login Faild";
		buffer = JsonResponsePacketSerializer::serializeErrorResponse(res);
	
		//create handler
		result.newHandler = m_handlerFactory.createLoginRequestHandler();
	}
	result.buffer = std::string(buffer.begin(), buffer.end());
	return result;
}

/*
analys the request and signup
in: request info
out: signup respons. if faild - error response
*/
RequestResult LoginRequestHandler::signup(RequestInfo r)
{
	RequestResult result;
	std::vector<unsigned char> buffer;
	SignupRequest request = JsonRequestPacketDeseializer::deserializeSignupRequest(r);
	bool worked = m_loginManager.signup(request.username, request.password, request.email);
	if (worked)
	{
		//create buffer
		SignupResponse res;
		res.status = SIGN_CODE;
		buffer = JsonResponsePacketSerializer::serializeSignUpResponse(res);
	
		//create handler
		result.newHandler = m_handlerFactory.createMenuRequestHandler(request.username);
	}
	else
	{
		//create buffer
		ErrorResponse res;
		res.message = "signup Faild";
		buffer = JsonResponsePacketSerializer::serializeErrorResponse(res);
	
		//create handler
		result.newHandler = m_handlerFactory.createLoginRequestHandler();
	}
	result.buffer = std::string(buffer.begin(), buffer.end());
	return result;
}
