#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include "User.h"
#include <io.h>

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

	virtual std::list<Question> getQuestions(int);
	virtual float getPlayerAverageAnswerTime(std::string);
	virtual int getNumOfCorrectAnswers(std::string);
	virtual int getNumOfTotalAnswers(std::string);
	virtual int getNumOfPlayerGames(std::string);

	virtual int getSecurityKey(std::string);

	//callback functions
	static int albumsCallback(void* data, int argc, char** argv, char** azColName);
	static int usersCallback(void* data, int argc, char** argv, char** azColName);
	static int tagsCallback(void* data, int argc, char** argv, char** azColName);
	static int picturesCallback(void* data, int argc, char** argv, char** azColName);
	static int singleFunctionalCallback(void* data, int argc, char** argv, char** azColName);

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
	static constexpr const char* K_ID_COLUMN = "K_ID";
	static constexpr const char* WINS_COLUMN = "WINS";
	static constexpr const char* GAMES_COLUMN = "GAMES";
	static constexpr const char* IS_ACTIVE_COLUMN = "IS_ACTIVE";

};
