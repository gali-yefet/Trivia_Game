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
	LoginRequest request = JsonRequestPacketDeseializer::deserializeLoginRequest(r);
	bool worked = m_loginManager.login(request.username, request.password);
	if (!worked)
	{
		ErrorResponse res;
		res.message = "Login Faild";
		std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeErrorResponse(res);
		return IRequestHandler::createRequestResult(buffer, this);
	}
	LoginResponse res;
	res.status = LOGIN_CODE;
	std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeLoginResponse(res);
	return IRequestHandler::createRequestResult(buffer, m_handlerFactory.createMenuRequestHandler(request.username));
}

/*
analys the request and signup
in: request info
out: signup respons. if faild - error response
*/
RequestResult LoginRequestHandler::signup(RequestInfo r)
{
	SignupRequest request = JsonRequestPacketDeseializer::deserializeSignupRequest(r);
	bool worked = m_loginManager.signup(request.username, request.password, request.email);
	if (!worked)
	{
		ErrorResponse res;
		res.message = "Signup Faild";
		std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeErrorResponse(res);
		return IRequestHandler::createRequestResult(buffer, this);
	}
	SignupResponse res;
	res.status = SIGN_CODE;
	std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeSignUpResponse(res);
	return IRequestHandler::createRequestResult(buffer, m_handlerFactory.createMenuRequestHandler(request.username));
}
