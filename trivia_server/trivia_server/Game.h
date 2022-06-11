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
	unsigned int averangeAnswerTime;
}GameData;

class Game
{
public:
	Game(std::vector<Question> m_questions, std::map<LoggedUser, GameData> m_players);
	std::string getQuestionForUser(User user);
	void submitAnswer(LoggedUser user, int answer);
	void removePlayer(User user);
	Question getCurrentQuestion(LoggedUser user);
	std::map<LoggedUser, GameData> getPlayers();
	bool isGameOver(LoggedUser user);

private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;

};