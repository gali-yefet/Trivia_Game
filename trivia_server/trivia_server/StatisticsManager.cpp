#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* db):
	m_database(db)
{
}

std::vector<std::string> StatisticsManager::getHighScore()
{
	std::vector<std::string> top5;
	std::list<userStatistics> users = this->m_database->getTopFive();
	userStatistics user;
	while(!users.empty())
	{ 
		user = users.front();
		top5.push_back("USERNAME: " + user.getUsername());
		top5.push_back("GAMES: " + user.getGames());
		top5.push_back("WINS: " + user.getWins());
		top5.push_back("AVERAGE TIME: " + user.getUsername());
		users.pop_front();
	}
	return top5;
}

std::vector<std::string> StatisticsManager::getUserStatistics(std::string username)
{
	userStatistics user = this->m_database->getUserStatistics(username);
	std::vector<std::string> statistics;
	statistics.push_back("USERNAME: " + user.getUsername());
	statistics.push_back("GAMES: " + user.getGames());
	statistics.push_back("WINS: " + user.getWins());
	statistics.push_back("AVERAGE TIME: " + static_cast<int>(user.getAveTime()));
	return statistics;
}
