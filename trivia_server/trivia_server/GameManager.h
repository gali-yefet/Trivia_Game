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

private:
	IDatabase* m_database;
	std::vector<Game*> m_games;
};
