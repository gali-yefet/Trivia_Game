#include "Game.h"


Game::Game(std::vector<Question> m_questions, std::map<LoggedUser, GameData> m_players):
	m_questions(m_questions), m_players(m_players)
{
}

std::string Game::getQuestionForUser(User user)
{
	std::string q;
	for (auto i = m_players.begin(); i != m_players.end(); ++i)
	{
		LoggedUser u = i->first;
		if (u.getUsername() == user.getUsername())
		{
			if(i->second.currentQuestion.getQuestion() != LEFT)
				q = i->second.currentQuestion.getQuestion(); //TODO: find out why it doesn't give the question...
		}
	}
	return q;
}

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

Question Game::getCurrentQuestion(LoggedUser user)
{
    auto it = m_players.find(user);
	if(it != m_players.end())// if pair found
		return it->second.currentQuestion;
	return Question();
}

std::map<LoggedUser, GameData> Game::getPlayers()
{
	return this->m_players;
}

bool Game::isGameOver(LoggedUser user)
{
	auto it = m_players.find(user);
	if(it != m_players.end())
		return (it->second.correctAnswerCount + it->second.wrongAnswerCount) == m_questions.size();
	return true;
}
