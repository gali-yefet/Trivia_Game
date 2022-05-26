#pragma once
#include "LoggedUser.h"
#include "Room.h"
#include <vector>
#include <map>

class RoomManager
{
public:
	void createRoom(LoggedUser user, RoomData data);
	void deleteRoom(int id);
	unsigned int getRoomState(int id);
	std::vector<RoomData> getRooms();
	Room& getRoom(int id);
	bool joinRoom(int id, LoggedUser user);
	int createRoomId();
	void changeRoomState(int id, int status);
	void deletePlayer(int id, std::string username);

private:
	std::map<unsigned int, Room> m_rooms; //<id, room>

};

