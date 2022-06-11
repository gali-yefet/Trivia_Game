#include "Game.h"


Game::Game(std::vector<Question> m_questions, std::map<LoggedUser, GameData> m_players):
	m_questions(m_questions), m_players(m_players)
{
}

//gets question for user
//input: user
//output: question
std::string Game::getQuestionForUser(LoggedUser user)
{
	std::string q;
	for (auto i = m_players.begin(); i != m_players.end(); ++i)
	{
		LoggedUser u = i->first;
		if (u.getUsername() == user.getUsername())
		{
			i->second.currentQuestion = m_questions[i->second.correctAnswerCount + i->second.wrongAnswerCount];
			if(i->second.currentQuestion.getQuestion() != LEFT)
				q = i->second.currentQuestion.getQuestion();
		}
	}
	return q;
}

//submit answer for user
//input: user
//output: none
void Game::submitAnswer(LoggedUser user, int answer)
{
	for (auto i = m_players.begin(); i != m_players.end(); ++i)
	{
		LoggedUser u = i->first;
		if (u.getUsername() == user.getUsername())
		{
			if (i->second.currentQuestion.getQuestion() != LEFT)
			{
				if (i->second.currentQuestion.getRightAns() == answer)
					i->second.correctAnswerCount++;
				else
					i->second.wrongAnswerCount++;
			}
		}
	}
}

//removes player from game
//input: user to remove
//output: none
void Game::removePlayer(User user)
{
	for (auto i = m_players.begin(); i != m_players.end(); ++i)
	{
		LoggedUser u = i->first;
		if (u.getUsername() == user.getUsername())
		{
			i->second.currentQuestion.setQuestion(LEFT);
		}
	}
}

//get current question for user
//input: user
//output: question
Question Game::getCurrentQuestion(LoggedUser user)
{
    auto it = m_players.find(user);
	if(it != m_players.end())// if pair found
		return it->second.currentQuestion;
	return Question();
}

//get players of game
std::map<LoggedUser, GameData> Game::getPlayers()
{
	return this->m_players;
}

//returns if game over
bool Game::isGameOver(LoggedUser user)
{
	auto it = m_players.find(user);
	if(it != m_players.end())
		return (it->second.correctAnswerCount + it->second.wrongAnswerCount) == m_questions.size();
	return true;
}
