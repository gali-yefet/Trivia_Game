#include "GameRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "define.h"

GameRequestHandler::GameRequestHandler(LoggedUser m_user, GameManager& gameManager, RequestHandlerFactory& handlerFactory, Room room):
    m_game(handlerFactory.getGameManager().createGame(room)), m_user(m_user), m_gameManager(gameManager), m_handlerFactory(handlerFactory)
{}

bool GameRequestHandler::isRequestRelevant(RequestInfo r)
{
	return r.requestCode == LEAVE_GAME ||
		r.requestCode == GET_QUESTION ||
		r.requestCode == SUBMIT_ANSWER ||
        r.requestCode == GET_GAME_RESULTS;
}

//handle's request
RequestResult GameRequestHandler::handleRequest(RequestInfo r)
{
    RequestResult result;
    switch (r.requestCode)
    {
    case LEAVE_GAME:
        result = leaveGame(r);
        break;
    case GET_QUESTION:
        result = getQuestion(r);
        break;
    case SUBMIT_ANSWER:
        result = submitAnswer(r);
        break;
    case GET_GAME_RESULTS:
        result = getGameResults(r);
        break;
    }
    return result;
}

//get question
//input: requestInfo
//output:request result
RequestResult GameRequestHandler::getQuestion(RequestInfo r)
{
    GetQuestionResponse response;
    response.status = GET_QUESTION;
    response.question = m_game->getQuestionForUser(m_user);
    response.answers = m_game->getCurrentQuestion(m_user).getAnswers();
    std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeGetQuestionResponse(response, m_game->isGameOver(m_user));
    return IRequestHandler::createRequestResult(buffer, this);
}

//submit answer
RequestResult GameRequestHandler::submitAnswer(RequestInfo r)
{
    SubmitAnswerRequest request = JsonRequestPacketDeseializer::deserializeSubmitAnswerRequest(r);
    SubmitAnswerResponse response;
    m_game->submitAnswer(m_user, request.answerId);
    response.status = SUBMIT_ANSWER;
    response.correctAnswerId = m_game->getCurrentQuestion(m_user).getRightAns();
    m_game->setPlayerAverageTime(request.time, m_user);
    std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeSubmitAnswerResponse(response);
    return IRequestHandler::createRequestResult(buffer, this);
}

//get game results
RequestResult GameRequestHandler::getGameResults(RequestInfo r)
{
    GetGameResultsResponse response;
    std::vector<PlayerResults> results;
    std::map<LoggedUser, GameData> players = m_game->getPlayers();
    bool allPlayersFinished = true;

    for (auto i = players.begin(); i != players.end(); ++i)
    {
        bool currentPlayerGameEnded = m_game->isGameOver(i->first);
        if (!currentPlayerGameEnded)
            allPlayersFinished = false;
    }

    if (allPlayersFinished)
    {
        response.status = GET_GAME_RESULTS;
        PlayerResults p;
        for (auto i = players.begin(); i != players.end(); ++i)
        {
            LoggedUser u = i->first;
            p.username = u.getUsername();
            p.correctAnswerCount = i->second.correctAnswerCount;
            p.wrongAnswerCount = i->second.wrongAnswerCount;
            p.averageAnswerTime = i->second.averageAnswerTime;
            results.push_back(p);
        }
        response.results = results;
    }
    
    std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeGetGameResultsResponse(response, allPlayersFinished); 
    return IRequestHandler::createRequestResult(buffer, this);
}

//leave game
RequestResult GameRequestHandler::leaveGame(RequestInfo r)
{
    m_game->removePlayer(m_user);
    LeaveGameResponse response;
    response.status = r.requestCode;
    std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeLeaveGameResponse(response);
    return IRequestHandler::createRequestResult(buffer, m_handlerFactory.createMenuRequestHandler(m_user.getUsername()));
}
