#pragma once
#include "Question.h"
#include "userStatistics.h"
#include <iostream>
#include <list>

class IDatabase
{
public:
	virtual bool open() = 0;
	virtual bool doesUserExist(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string username, std::string password) = 0;
	virtual void addNewUser(std::string username, std::string password, std::string email) = 0;
	virtual void login(std::string username) = 0;
	virtual void logout(std::string username) = 0;
	virtual bool isActive(std::string username) = 0;

	virtual void createQuestions() = 0;
	virtual void getQuestions(int limit, std::list<Question>& listOfQuestions) = 0;
	virtual float getPlayerAverageAnswerTime(std::string) = 0;
	virtual int getNumOfCorrectAnswers(std::string) = 0;
	virtual int getNumOfTotalAnswers(std::string) = 0;
	virtual int getNumOfPlayerGames(std::string) = 0;
	virtual userStatistics getUserStatistics(std::string username) = 0;
	virtual int getSecurityKey(std::string) = 0;
	virtual std::list<userStatistics> getTopFive() = 0;
};
