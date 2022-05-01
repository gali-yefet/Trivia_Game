#include "Room.h"

/*
create a new room according to the user who created it, and its data
in: user, room data
*/
Room::Room(LoggedUser user, RoomData data):
	m_metadata(data)
{
	m_users.push_back(user);
}

/*
add user to the room
in: user
out: void
*/
void Room::addUser(LoggedUser user)
{
	m_users.push_back(user);
}

/*
remove user from the room
in: user
out: void
*/
void Room::removeUser(LoggedUser user)
{
	for (auto i = m_users.begin(); i != m_users.end(); ++i)
	{
		if (i->getUsername() == user.getUsername())
		{
			m_users.erase(i);
			break;
		}
	}
}

/*
get a list of all the users in the room
in: void
out: vector of the users usernames
*/
std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> list;
	for (auto i = m_users.begin(); i != m_users.end(); ++i)
		list.push_back(i->getUsername());
	return list;
}
