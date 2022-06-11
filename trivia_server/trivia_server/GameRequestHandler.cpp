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
    case GET_GAME_RESULTS:
        result = getGameResults(r);
        break;
    }
    return result;
}

RequestResult GameRequestHandler::getQuestion(RequestInfo r)
{
    GetQuestionResponse response;
    response.status = GET_QUESTION;
    response.question = m_game.getQuestionForUser(m_user);
    response.answers = m_game.getCurrentQuestion(m_user).getAnswers();
    std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeGetQuestionResponse(response, m_game.isGameOver(m_user));
    return IRequestHandler::createRequestResult(buffer, this);
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo r)
{
    SubmitAnswerRequest request = JsonRequestPacketDeseializer::deserializeSubmitAnswerRequest(r);
    SubmitAnswerResponse response;
    m_game.submitAnswer(m_user, request.answerId);
    response.status = SUBMIT_ANSWER;
    response.correctAnswerId = m_game.getCurrentQuestion(m_user).getRightAns();
    m_game.setPlayerAverageTime(request.time, m_user);
    std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeSubmitAnswerResponse(response);
    return IRequestHandler::createRequestResult(buffer, this);
}

RequestResult GameRequestHandler::getGameResults(RequestInfo r)
{
    GetGameResultsResponse response;
    response.status = GET_GAME_RESULTS;
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

    std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeGetGameResultsResponse(response, m_game.isGameOver(m_user));
    return IRequestHandler::createRequestResult(buffer, this);
}

RequestResult GameRequestHandler::leaveGame(RequestInfo r)
{
    User u = User();
    u.setUsername(m_user.getUsername());
    m_game.removePlayer(u);
    LeaveGameResponse response;
    response.status = r.requestCode;
    std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeLeaveGameResponse(response);
    return IRequestHandler::createRequestResult(buffer, m_handlerFactory.createMenuRequestHandler(m_user.getUsername()));
}
