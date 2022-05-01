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
		/*res = query("CREATE TABLE IF NOT EXISTS QUESTION (Q_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, K_ID INTEGER NOT NULL, FOREIGN KEY(K_ID) REFERENCES KEY(ID));");
		if (!res)
			std::cout << "Failed to create Table QUESTION" << std::endl;
		res = query("CREATE TABLE IF NOT EXISTS STATISTICS (USERNAME TEXT PRIMARY KEY AUTOINCREMENT NOT NULL, WINS INTEGER NOT NULL, GAMES INTEGER NOT NULL, FOREIGN KEY(USERNAME) REFERENCES USER(USERNAME));");
		if (!res)
			std::cout << "Failed to create Table STATISTICS" << std::endl;
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

std::list<Question> SqliteDataBase::getQuestions(int) //TODO
{
	return std::list<Question>();
}

float SqliteDataBase::getPlayerAverageAnswerTime(std::string)//TODO
{
	return 0.0f;
}

int SqliteDataBase::getNumOfCorrectAnswers(std::string)//TODO
{
	return 0;
}

int SqliteDataBase::getNumOfTotalAnswers(std::string)//TODO
{
	return 0;
}

int SqliteDataBase::getNumOfPlayerGames(std::string)//TODO
{
	return 0;
}

int SqliteDataBase::getSecurityKey(std::string)//TODO
{
	return 0;
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
