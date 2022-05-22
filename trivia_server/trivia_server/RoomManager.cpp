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

/*
get referance to room according to id
in: room id
out: room
*/
Room& RoomManager::getRoom(int id)
{
	return m_rooms.find(id)->second;
}

/*
join a room according to id
in: id, user to join
out: bool- true if joined
*/
bool RoomManager::joinRoom(int id, LoggedUser user)
{
	return m_rooms.find(id)->second.addUser(user);
}

/*
get a room id that isn't used already
in: void
out: room id
*/
int RoomManager::createRoomId()
{
	for (int i = 0; i < m_rooms.size() + 1; i++)
		if (m_rooms.find(i) == m_rooms.end())
			return i;
}

void RoomManager::changeRoomState(int id, int status)
{
	for (auto i = m_rooms.begin(); i != m_rooms.end(); ++i)
	{
		if (i->first == id)
		{
			RoomData roomData;
			roomData.id = id;
			roomData.isActive = status;
			roomData.maxPlayers = i->second.getRoomData().maxPlayers;
			roomData.name = i->second.getRoomData().name;
			roomData.numOfQuestionsInGame = i->second.getRoomData().numOfQuestionsInGame;
			roomData.timePerQuestion = i->second.getRoomData().timePerQuestion;
			i->second.setRoomData(roomData);
		}
	}
}

void RoomManager::deletePlayer(int id, std::string username)
{
	m_rooms.find(id)->second.removeUser(LoggedUser(username));
}
