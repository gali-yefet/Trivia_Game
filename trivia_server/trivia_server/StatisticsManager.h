#pragma once
#include "IDatabase.h"
#include "SqliteDataBase.h"
#include <string.h>
#include <vector>

class StatisticsManager
{
public:
	StatisticsManager(IDatabase* db);
	void getHighScore(std::vector<std::string>& top5);
	void getUserStatistics(std::string username, std::vector<std::string>& userStat);

private:
	IDatabase* m_database;
};