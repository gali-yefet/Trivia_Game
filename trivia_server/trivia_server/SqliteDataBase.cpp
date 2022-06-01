#include "SqliteDataBase.h"

SqliteDataBase::SqliteDataBase()
{
	open();
}

bool SqliteDataBase::open()
{
	int doesFileExist = _access(DB_FILE_NAME, 0);
	int res = sqlite3_open(DB_FILE_NAME, &_db);
	if (res != SQLITE_OK) {
		_db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}

	if (doesFileExist != 0) {
		// init database
		bool res = query("CREATE TABLE IF NOT EXISTS USER (USERNAME TEXT PRIMARY KEY NOT NULL, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL, IS_ACTIVE INTEGER NOT NULL);");
		if (!res)
			std::cout << "Failed to create Table USER" << std::endl;
		res = query("CREATE TABLE IF NOT EXISTS QUESTION (Q_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, QUESTION TEXT NOT NULL, ANS1 TEXT NOT NULL, ANS2 TEXT NOT NULL, ANS3 TEXT NOT NULL, ANS4 TEXT NOT NULL, RIGHT_ANS INTEGER NOT NULL);");
		if (!res)
			std::cout << "Failed to create Table QUESTION" << std::endl;
		res = query("CREATE TABLE IF NOT EXISTS STATISTICS (USERNAME TEXT PRIMARY KEY NOT NULL, WINS INTEGER NOT NULL, GAMES INTEGER NOT NULL, AVE_TIME REAL NOT NULL, CORRECT_ANS INTEGER NOT NULL, TOTAL_ANS INTEGER NOT NULL, FOREIGN KEY(USERNAME) REFERENCES USER(USERNAME));");
		if (!res)
			std::cout << "Failed to create Table STATISTICS" << std::endl;
		/*
		res = query("CREATE TABLE IF NOT EXISTS GAME (GAME_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL;");
		if (!res)
			std::cout << "Failed to create Table GAME" << std::endl;
		res = query("CREATE TABLE IF NOT EXISTS KEY (KEY_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, Q_ID INTEGER NOT NULL, ANS_ID INTEGER NOT NULL, FOREIGN KEY(Q_ID) REFERENCES QUESTION(Q_ID));");
		if (!res)
			std::cout << "Failed to create Table KEY" << std::endl;
			*/
	}

	return true;

}

bool SqliteDataBase::doesUserExist(std::string username)
{
	std::string q = "SELECT * FROM USER where USERNAME = '" + username + "';";
	std::list<User> listOfUsers;
	this->execSelectCmd(q.c_str(), this->usersCallback, &listOfUsers);
	return listOfUsers.size() != 0;
}

bool SqliteDataBase::doesPasswordMatch(std::string username, std::string password)
{
	std::string q = "SELECT PASSWORD FROM USER where USERNAME = '" + username + "';";
	std::list<User> listOfUsers;
	this->execSelectCmd(q.c_str(), this->usersCallback, &listOfUsers);
	User currentUser = listOfUsers.front();

	return currentUser.getPassword() == password;
}

void SqliteDataBase::addNewUser(std::string username, std::string password, std::string email)
{
	std::string q = "INSERT INTO USER(USERNAME, PASSWORD, EMAIL, IS_ACTIVE) VALUES('" + username + "', '" + password + "', '" + email + "', 1); ";
	query(q.c_str());
}

void SqliteDataBase::login(std::string username)
{
	std::string q = "UPDATE USER SET IS_ACTIVE = 1 WHERE USERNAME = '" + username + "';";
	query(q.c_str());
}

void SqliteDataBase::logout(std::string username)
{
	std::string q = "UPDATE USER SET IS_ACTIVE = 0 WHERE USERNAME = '" + username + "';";
	std::cerr << "loged out" << std::endl;//TODO: erase
	query(q.c_str());
}

bool SqliteDataBase::isActive(std::string username)
{
	std::string q = "SELECT IS_ACTIVE FROM USER WHERE USERNAME = '" + username + "';";
	std::list<User> listOfUsers;
	this->execSelectCmd(q.c_str(), this->usersCallback, &listOfUsers);
	User currentUser = listOfUsers.front();

	return currentUser.getIsActive() == 1;
}

void SqliteDataBase::createQuestions()
{
	std::string q = "";
	int j = 0;
	for (int i = 0; i < questions->length(); i++)
	{
		q = "INSERT INTO QUESTION (QUESTION, ANS1, ANS2, ANS3, ANS4, RIGHT_ANS) VALUES('" + questions[i] + "', '";
		for (int k = 0; k < ANSWERS; k++)
		{
			if (k == ANSWERS - 1)
				q += answers[j] + "', ";
			else
				q += answers[j] + "', '";
			j++;
		}
		q += rightAns[i] + ");";
		query(q.c_str());
	}
}

std::list<Question> SqliteDataBase::getQuestions(int limit)
{
	std::string q = "SELECT * FROM QUESTION LIMIT " + std::to_string(limit) + "; ";
	std::list<Question> listOfQuestions;
	this->execSelectCmd(q.c_str(), this->questionsCallback, &listOfQuestions);

	return listOfQuestions;
}

float SqliteDataBase::getPlayerAverageAnswerTime(std::string username)
{
	std::string q = "SELECT AVE_TIME FROM STATISTICS WHERE USERNAME = '" + username + "';";
	std::list<userStatistics> listOfUsers;
	this->execSelectCmd(q.c_str(), this->userStatisticsCallback, &listOfUsers);
	userStatistics currentUser = listOfUsers.front();

	return currentUser.getAveTime();
}

int SqliteDataBase::getNumOfCorrectAnswers(std::string username)
{
	std::string q = "SELECT CORRECT_ANS FROM STATISTICS WHERE USERNAME = '" + username + "';";
	std::list<userStatistics> listOfUsers;
	this->execSelectCmd(q.c_str(), this->userStatisticsCallback, &listOfUsers);
	userStatistics currentUser = listOfUsers.front();

	return currentUser.getAveTime();
}

int SqliteDataBase::getNumOfTotalAnswers(std::string username)
{
	std::string q = "SELECT TOTAL_ANS FROM STATISTICS WHERE USERNAME = '" + username + "';";
	std::list<userStatistics> listOfUsers;
	this->execSelectCmd(q.c_str(), this->userStatisticsCallback, &listOfUsers);
	userStatistics currentUser = listOfUsers.front();

	return currentUser.getTotalAns();
}

int SqliteDataBase::getNumOfPlayerGames(std::string username)
{
	std::string q = "SELECT GAMES FROM STATISTICS WHERE USERNAME = '" + username + "';";
	std::list<userStatistics> listOfUsers;
	this->execSelectCmd(q.c_str(), this->userStatisticsCallback, &listOfUsers);
	userStatistics currentUser = listOfUsers.front();

	return currentUser.getGames();
}

userStatistics SqliteDataBase::getUserStatistics(std::string username)
{
	userStatistics currentUser = userStatistics();
	std::string q = "SELECT * FROM STATISTICS WHERE USERNAME = '" + username + "';";
	std::list<userStatistics> listOfUsers;
	this->execSelectCmd(q.c_str(), this->userStatisticsCallback, &listOfUsers);
	if(!listOfUsers.empty())
		currentUser = listOfUsers.front();

	return currentUser;
}

int SqliteDataBase::getSecurityKey(std::string username)//TODO
{
	return 0;
}

std::list<userStatistics> SqliteDataBase::getTopFive()
{
	std::string q = "SELECT * FROM STATISTICS ORDER BY WINS DESC, AVE_TIME ASC LIMIT 5;";
	std::list<userStatistics> listOfUsers;
	this->execSelectCmd(q.c_str(), this->userStatisticsCallback, &listOfUsers);
	return listOfUsers;
}



//call backs
int SqliteDataBase::usersCallback(void* data, int argc, char** argv, char** azColName)
{
	std::list<User>* now = (std::list<User>*)data;
	User currUser;
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == USERNAME_COLUMN)
			currUser.setUsername(argv[i]);
		else if (std::string(azColName[i]) == PASSWORD_COLUMN)
			currUser.setPassword(argv[i]);
		else if (std::string(azColName[i]) == EMAIL_COLUMN)
			currUser.setEmail(argv[i]);
		else if (std::string(azColName[i]) == IS_ACTIVE_COLUMN)
			currUser.setIsActive(std::stoi(argv[i]));
	}
	now->push_back(currUser);
	return 0;
}

int SqliteDataBase::userStatisticsCallback(void* data, int argc, char** argv, char** azColName)
{
	std::list<userStatistics>* now = (std::list<userStatistics>*)data;
	userStatistics currUser;
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == USERNAME_COLUMN)
			currUser.setUsername(argv[i]);
		else if (std::string(azColName[i]) == GAMES_COLUMN)
			currUser.setGames(std::stoi(argv[i]));
		else if (std::string(azColName[i]) == WINS_COLUMN)
			currUser.setWins(std::stoi(argv[i]));
		else if (std::string(azColName[i]) == AVE_TIME_COLUMN)
			currUser.setAveTime(std::stoi(argv[i]));

	}
	now->push_back(currUser);
	return 0;
}

int SqliteDataBase::questionsCallback(void* data, int argc, char** argv, char** azColName)
{
	std::list<Question>* now = (std::list<Question>*)data;
	Question currQ;
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == QUESTION_COLUMN)
			currQ.setQuestion(argv[i]);
		else if (std::string(azColName[i]) == ANS1_COLUMN)
			currQ.setAns1(argv[i]);
		else if (std::string(azColName[i]) == ANS2_COLUMN)
			currQ.setAns2(argv[i]);
		else if (std::string(azColName[i]) == ANS3_COLUMN)
			currQ.setAns3(argv[i]);
		else if (std::string(azColName[i]) == ANS4_COLUMN)
			currQ.setAns4(argv[i]);
		else if (std::string(azColName[i]) == RIGHT_ANS_COLUMN)
			currQ.setRightAns(std::stoi(argv[i]));
	}
	now->push_back(currQ);
	return 0;
}



//private
bool SqliteDataBase::query(const char* sqlStatement)
{
	const char* sql_statement = sqlStatement;

	char* errMessage = nullptr;
	int res = sqlite3_exec(_db, sql_statement, nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cerr << sqlStatement << ":\n" << errMessage << std::endl;
		return false;
	}

	return true;

}

void SqliteDataBase::execSelectCmd(const char* sqlStatement, int(*callback)(void*, int, char**, char**), void* callbackParam)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(_db, sqlStatement, callback, callbackParam, &errMessage);
	if (res != SQLITE_OK) // (errMessage != nullptr)
		throw std::exception(errMessage);

}
