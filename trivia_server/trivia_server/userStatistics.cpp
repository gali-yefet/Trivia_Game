#include "userStatistics.h"


userStatistics::userStatistics(std::string username, float aveTime, int games, int wins, int correctAns, int totalAns)
	:username(username), aveTime(aveTime), games(games), wins(wins), correctAns(correctAns), totalAns(totalAns)
{}

std::string userStatistics::getUsername()
{
	return this->username;
}

float userStatistics::getAveTime()
{
	return this->aveTime;
}

int userStatistics::getGames()
{
	return this->games;
}

int userStatistics::getWins()
{
	return this->wins;
}

int userStatistics::getCorrectAns()
{
	return this->correctAns;
}

int userStatistics::getTotalAns()
{
	return this->totalAns;
}

void userStatistics::setUsername(std::string username)
{
	this->username = username;
}

void userStatistics::setAveTime(const float aveTime)
{
	this->aveTime = aveTime;
}

void userStatistics::setGames(const int games)
{
	this->games = games;
}

void userStatistics::setWins(const int wins)
{
	this->wins = wins;
}

void userStatistics::setCorrectAns(int correctAns)
{
	this->correctAns = correctAns;
}

void userStatistics::setTotalAns(int totalAns)
{
	this->totalAns = totalAns;
}
