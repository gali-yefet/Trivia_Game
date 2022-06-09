#include "GameManager.h"

GameManager::GameManager(IDatabase* db)
    : m_database(db)
{}

Game GameManager::createGame(Room room)
{
	//get random questions for the game
	std::list<Question> list = m_database->getQuestions(room.getRoomData().numOfQuestionsInGame);
	std::vector<Question> questions(list.begin(), list.end());
	std::random_shuffle(questions.begin(), questions.end());

	//set the players for the game
	std::map<LoggedUser, GameData> players;
	std::vector<std::string> users = room.getAllUsers();
	for (auto i = users.begin(); i != users.end(); ++i)
	{
		players.emplace(LoggedUser(i->data()), GameData());//TODO: set basic game data
	}

	//create game
	Game game(questions, players);
	m_games.push_back(game);
	return game;
}

void GameManager::deleteGame()
{
	this->m_games.clear();
}
