#pragma once
#include <iostream>
#include "LoggedUser.h"
#include <vector>

typedef struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
}RoomData;

class Room
{
public:
	Room(LoggedUser user, RoomData data);
	bool addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers();
	RoomData getRoomData();
	void setRoomData(RoomData roomData);

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};

