#pragma once
#include "LoggedUser.h"
#include "Room.h"
#include <vector>
#include <map>

class RoomManager
{
public:
	void createRoom(LoggedUser user, RoomData data);
	void deleteRoom( int id);
	unsigned int getRoomState(int id);
	std::vector<RoomData> getRooms();
	Room& getRoom(int id);
	void joinRoom(int id, LoggedUser user);
	int createRoomId();

private:
	std::map<unsigned int, Room> m_rooms; //<id, room>

};

