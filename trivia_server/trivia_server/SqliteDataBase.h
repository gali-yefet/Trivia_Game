#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include "User.h"
#include "userStatistics.h"
#include <io.h>
#include "define.h"

class SqliteDataBase : public IDatabase
{
public:
	SqliteDataBase();
	virtual bool open();
	virtual bool doesUserExist(std::string username);
	virtual bool doesPasswordMatch(std::string username, std::string password);
	virtual void addNewUser(std::string username, std::string password, std::string email);
	virtual void login(std::string username);
	virtual void logout(std::string username);
	virtual bool isActive(std::string username);

	virtual void createQuestions();
	virtual void getQuestions(int limit, std::list<Question>& listOfQuestions);
	virtual float getPlayerAverageAnswerTime(std::string username);
	virtual int getNumOfCorrectAnswers(std::string username);
	virtual int getNumOfTotalAnswers(std::string username);
	virtual int getNumOfPlayerGames(std::string username);
	virtual int getNumOfPlayerWins(std::string username);
	virtual void submitAnswer(bool correct, std::string username);
	virtual void setTime(double time, std::string username);
	virtual void updateWins(std::string username);
	virtual void updateGames(std::string username);
	virtual userStatistics getUserStatistics(std::string username);
	virtual int getSecurityKey(std::string);
	virtual void getTopFive(std::list<userStatistics>& listOfUsers);

	//callback functions
	static int questionsCallback(void* data, int argc, char** argv, char** azColName);
	static int usersCallback(void* data, int argc, char** argv, char** azColName);
	static int userStatisticsCallback(void* data, int argc, char** argv, char** azColName);

private:
	bool query(const char* sqlStatement);
	void execSelectCmd(const char* sqlStatement, int (*callback)(void*, int, char**, char**), void* callbackParam);

	sqlite3* _db;

	//define some variables
	const char* DB_FILE_NAME = "DB.sqlite";

	// tables names
	static constexpr const char* USER_TABLE = "USER";
	static constexpr const char* QUESTION_TABLE = "QUESTION";
	static constexpr const char* STATISTICS_TABLE = "STATISTICS";
	static constexpr const char* GAME_TABLE = "GAME";
	static constexpr const char* KEY_TABLE = "KEY";

	// columns names
	static constexpr const char* USERNAME_COLUMN = "USERNAME";
	static constexpr const char* PASSWORD_COLUMN = "PASSWORD";
	static constexpr const char* EMAIL_COLUMN = "EMAIL";
	static constexpr const char* Q_ID_COLUMN = "Q_ID";
	static constexpr const char* QUESTION_COLUMN = "QUESTION";
	static constexpr const char* ANS1_COLUMN = "ANS1";
	static constexpr const char* ANS2_COLUMN = "ANS2";
	static constexpr const char* ANS3_COLUMN = "ANS3";
	static constexpr const char* ANS4_COLUMN = "ANS4";
	static constexpr const char* RIGHT_ANS_COLUMN = "RIGHT_ANS";
	static constexpr const char* K_ID_COLUMN = "K_ID";
	static constexpr const char* WINS_COLUMN = "WINS";
	static constexpr const char* GAMES_COLUMN = "GAMES";
	static constexpr const char* IS_ACTIVE_COLUMN = "IS_ACTIVE";
	static constexpr const char* AVE_TIME_COLUMN = "AVE_TIME";
	static constexpr const char* CORRECT_ANS_COLUMN = "CORRECT_ANS";
	static constexpr const char* TOTAL_ANS_COLUMN = "TOTAL_ANS";


};
