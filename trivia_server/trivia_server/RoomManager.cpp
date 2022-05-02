#include "RoomManager.h"

/*
create a room and put it in the map
in: user and room data
out: void
*/
void RoomManager::createRoom(LoggedUser user, RoomData data)
{
	m_rooms.emplace(data.id, Room(user, data));
}

/*
delete a room from the map
in: id
out: void
*/
void RoomManager::deleteRoom(int id)
{
	for (auto i = m_rooms.begin(); i != m_rooms.end(); ++i)
	{
		if (i->first == id)
		{
			m_rooms.erase(i);
			break;
		}
	}
}

/*
get the room state
in: room id
out: state
*/
unsigned int RoomManager::getRoomState(int id)
{
	for (auto i = m_rooms.begin(); i != m_rooms.end(); ++i)
		if (i->first == id)
			return i->second.getRoomData().isActive;
}

/*
get a list odf all the rooms data
in: void
out: vector of the rooms data
*/
std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> list;
	for (auto i = m_rooms.begin(); i != m_rooms.end(); ++i)
		list.push_back(i->second.getRoomData());
	return list;
}
