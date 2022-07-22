#pragma once
#include <string>
#include <iostream>

class userStatistics
{
public:

	userStatistics() = default;
	userStatistics(std::string username, float aveTime, int games, int wins, int correctAns, int totalAns);

	std::string getUsername();
	float getAveTime();
	int getGames();
	int getWins();
	int getCorrectAns();
	int getTotalAns();

	void setUsername(std::string username);
	void setAveTime(const float aveTime);
	void setGames(const int games);
	void setWins(const int wins);
	void setCorrectAns(int correctAns);
	void setTotalAns(int totalAns);

private:
	std::string username;
	float aveTime;
	int games;
	int wins;
	int correctAns;
	int totalAns;
};