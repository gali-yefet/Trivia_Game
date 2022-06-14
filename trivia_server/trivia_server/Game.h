#pragma once
#include "Question.h"
#include "LoggedUser.h"
#include "User.h"
#include "Room.h"
#include <iostream>
#include <vector>
#include <map>


typedef struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
}GameData;

class Game
{
public:
	Game(std::vector<Question> m_questions, std::map<LoggedUser, GameData> m_players, int id);
	std::string getQuestionForUser(LoggedUser user);
	void submitAnswer(LoggedUser user, int answer);
	void removePlayer(LoggedUser user);
	Question getCurrentQuestion(LoggedUser user);
	void setPlayerAverageTime(int time, LoggedUser user);
	std::map<LoggedUser, GameData> getPlayers();
	bool isGameOver(LoggedUser user);
	int getId();

private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	int m_gameId;
};