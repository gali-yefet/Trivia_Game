#pragma once
#include "IRequestHandler.h"
#include "GameManager.h"
#include "RequestHandlerFactory.h"

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(LoggedUser m_user, GameManager& gameManager, RequestHandlerFactory& handlerFactory, Room room);
	virtual bool isRequestRelevant(RequestInfo r); 
	virtual RequestResult handleRequest(RequestInfo r); 

private:
	RequestResult getQuestion(RequestInfo r);
	RequestResult submitAnswer(RequestInfo r);
	RequestResult getGameResults(RequestInfo r);
	RequestResult leaveGame(RequestInfo r);

	Game m_game;
	LoggedUser m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;
};

