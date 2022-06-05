#include "GameRequestHandler.h"
#include "define.h"
#include "RoomMemberRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

GameRequestHandler::GameRequestHandler(Game m_game, LoggedUser m_user, GameManager& m_gameManager, RequestHandlerFactory& m_handlerFacroty)
    :m_game(m_game), m_user(m_user), m_gameManager(m_gameManager), m_handlerFactory(m_handlerFacroty)
{}

bool GameRequestHandler::isRequestRelevant(RequestInfo r)
{
	return r.requestCode == LEAVE_GAME ||
		r.requestCode == GET_QUESTION ||
		r.requestCode == SUBMIT_ANSWER ||
        r.requestCode == GET_GAME_RESULT;
    r.requestCode == GET_GAME_RESULT;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo r)
{
    RequestResult result;
    switch (r.requestCode)
    {
    case LEAVE_ROOM:
        result = leaveGame(r);
        break;
    case GET_QUESTION:
        result = getQuestion(r);
        break;
    case SUBMIT_ANSWER:
        result = submitAnswer(r);
        break;
    case GET_GAME_RESULT:
        result = getGameResults(r);
        break;
    }
    return result;
}

RequestResult GameRequestHandler::getQuestion(RequestInfo r)
{
    GetQuestionResponse response;
    response.status = GET_QUESTION;
    User u;
    u.setUsername(m_user.getUsername());
    response.question = m_game.getQuestionForUser(u);
    response.answers = m_game.getCurrentQuestion(m_user).getAnswers();
    std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeGetQuestionResponse(response);
    return IRequestHandler::createRequestResult(buffer, m_handlerFactory.createGameRequestHandler(m_game, m_user));
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo r)
{
    SubmitAnswerRequest request = JsonRequestPacketDeseializer::deserializeSubmitAnswerRequest(r);
    SubmitAnswerResponse response;
    response.status = SUBMIT_ANSWER;
    response.correctAnswerId = 6;// TODO: GET THE CORRECT ASW ID
    std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeSubmitAnswerResponse(response);
    return IRequestHandler::createRequestResult(buffer, m_handlerFactory.createGameRequestHandler(m_game, m_user));
}

RequestResult GameRequestHandler::getGameResults(RequestInfo r)
{
    GetGameResultsResponse response;
    response.status = GET_GAME_RESULT;
    std::vector<PlayerResults> results;
    std::map<LoggedUser, GameData> players = m_game.getPlayers();
    PlayerResults p;
    for (auto i = players.begin(); i != players.end(); ++i)
    {
        LoggedUser u = i->first;
        p.username = u.getUsername();
        p.correctAnswerCount = i->second.correctAnswerCount;
        p.wrongAnswerCount = i->second.wrongAnswerCount;
        p.averageAnserTime = i->second.averangeAnswerTime;
        results.push_back(p);
    }
    response.results = results;
    std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeGetGameResultsResponse(response);
    return IRequestHandler::createRequestResult(buffer, m_handlerFactory.createGameRequestHandler(m_game, m_user));
}

RequestResult GameRequestHandler::leaveGame(RequestInfo r)
{
    User u = User();
    u.setUsername(m_user.getUsername());
    m_game.removePlayer(u);
    LeaveGameResponse response;
    response.status = r.requestCode;
    std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeLeaveGameResponse(response);
    return IRequestHandler::createRequestResult(buffer, m_handlerFactory.createGameRequestHandler(m_game, m_user));
}
