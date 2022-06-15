#include "GameManager.h"

GameManager::GameManager(IDatabase* db):
	m_database(db)
{}

//start game
//input: room
//output: new game for the room
Game* GameManager::createGame(Room room)
{
	//check if the game of the room is already open
	for (int i = 0; i < m_games.size(); i++)
	{
		Game* currentGame = m_games[i];
		if (room.getRoomData().id == currentGame->getId())
			return currentGame;
	}


	//get random questions for the game
	std::list<Question> listOfQuestions;
	m_database->getQuestions(room.getRoomData().numOfQuestionsInGame, listOfQuestions);
	std::vector<Question> questions(listOfQuestions.begin(), listOfQuestions.end());
	std::random_shuffle(questions.begin(), questions.end());

	//set the players for the game
	std::map<LoggedUser, GameData> players;
	std::vector<std::string> users = room.getAllUsers();
	for (auto i = users.begin(); i != users.end(); ++i)
	{
		GameData d;
		if (questions.size() > 0)
			d.currentQuestion = questions[0];
		d.averageAnswerTime = 0;
		d.correctAnswerCount = 0;
		d.wrongAnswerCount = 0;
		players.emplace(LoggedUser(*i), d);
	}

	//create game
	Game* game = new Game(questions, players, room.getRoomData().id);
	m_games.push_back(game);
	return game;
}

//delete games
void GameManager::deleteGame()
{
	this->m_games.clear();
}

void GameManager::updateDB(bool isCorrect, bool won, bool finished, double time, std::string username)
{
	m_database->submitAnswer(isCorrect, username);
	m_database->setTime(time, username);
	if(won)
		m_database->updateWins(username);
	if (finished)
		m_database->updateGames(username);
}
