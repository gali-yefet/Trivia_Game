#pragma once
#include "Room.h"
#include "Game.h"
#include "IDatabase.h"
#include <random>

class GameManager {
public:
	GameManager(IDatabase* db);
	Game* createGame(Room room);
	void deleteGame();
	void updateDB(bool isCorrect, bool won, bool finished, double time, std::string username);


private:
	IDatabase* m_database;
	std::vector<Game*> m_games;
};
