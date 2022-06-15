#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* db):
	m_database(db)
{
}

void StatisticsManager::getHighScore(std::vector<std::string>& top5)
{
	std::list<userStatistics> users;
	this->m_database->getTopFive(users);
	userStatistics user;
	while(!users.empty())
	{ 
		user = users.front();
		top5.push_back("USERNAME: " + user.getUsername());
		top5.push_back("GAMES: " + std::to_string(user.getGames()));
		top5.push_back("WINS: " + std::to_string(user.getWins()));
		top5.push_back("AVERAGE TIME: " + std::to_string((int)user.getAveTime()));
		users.pop_front();
	}
}

void StatisticsManager::getUserStatistics(std::string username, std::vector<std::string>& userStat)
{
	userStatistics user = this->m_database->getUserStatistics(username);
	userStat.push_back("USERNAME: " + user.getUsername());
	userStat.push_back("GAMES: " + std::to_string(user.getGames()));
	userStat.push_back("WINS: " + std::to_string(user.getWins()));
	userStat.push_back("AVERAGE TIME: " + std::to_string((int)user.getAveTime()));
}
