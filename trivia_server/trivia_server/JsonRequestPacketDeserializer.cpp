#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include <string>
#include <iostream>
#include <algorithm>


LoginRequest JsonRequestPacketDeseializer::deserializeLoginRequest(RequestInfo r)
{
	LoginRequest l;
	if(r.requestCode == LOGIN_CODE)
	{
		std::string data(r.json.begin(), r.json.end());// converts the data from bytes to string
		//now the data looks like this:
		//{ username: <username>, password: <password> }
		
		l.username = extractValue(data);
		l.password = extractValue(data);
	}
	return l;
}

SignupRequest JsonRequestPacketDeseializer::deserializeSignupRequest(RequestInfo r)
{
	SignupRequest s;
	if (r.requestCode == SIGN_CODE)
	{
		std::string data(r.json.begin(), r.json.end());// converts the data from bytes to string
		//now the data looks like this:
		//{ username: <username>, password: <password>, email:<email> }

		s.username = extractValue(data);
		s.password = extractValue(data);
		s.email = extractValue(data);
	}
	return s;
}

GetPlayersInRoomRequest JsonRequestPacketDeseializer::deserializeGetPlayersInRoomRequest(RequestInfo r)
{
	GetPlayersInRoomRequest g;
	if (r.requestCode == GET_PLAYERS_IN_ROOM)
	{
		std::string data(r.json.begin(), r.json.end());// converts the data from bytes to string
		//now the data looks like this:
		//{ username: <username>, password: <password>, email:<email> }

		try
		{
			g.roomId = std::stoi(extractValue(data, true));
		}
		catch (const std::exception& e)
		{
			std::cout << "Exception was thrown in JsonRequestPacketDeseializer::deserializeGetPlayersInRoomRequest: " << e.what() << std::endl;
		}
	}
	return g;
}

JoinRoomRequest JsonRequestPacketDeseializer::deserializeJoinRoomRequest(RequestInfo r)
{
	JoinRoomRequest j;
	if (r.requestCode == JOIN_ROOM)
	{
		std::string data(r.json.begin(), r.json.end());// converts the data from bytes to string
		//now the data looks like this:
		//{ username: <username>, password: <password>, email:<email> }

		try
		{
			j.roomId = std::stoi(extractValue(data));
		}
		catch (const std::exception& e)
		{
			std::cout << "Exception was thrown in JsonRequestPacketDeseializer::deserializeJoinRoomRequest: " << e.what() << std::endl;
		}
	}
	return j;
}

CreateRoomRequest JsonRequestPacketDeseializer::deserializeCreateRoomRequest(RequestInfo r)
{
	CreateRoomRequest c;
	if (r.requestCode == CREATE_ROOM)
	{
		std::string data(r.json.begin(), r.json.end());// converts the data from bytes to string
		//now the data looks like this:
		//{ username: <username>, password: <password>, email:<email> }

		try
		{
			c.roomName = extractValue(data);
			c.maxUsers = std::stoi(extractValue(data));
			c.questionCount = std::stoi(extractValue(data));
			c.answerTimeOut = std::stoi(extractValue(data));
		}
		catch (const std::exception& e)
		{
			std::cout << "Exception was thrown in JsonRequestPacketDeseializer::deserializeCreateRoomRequest: " << e.what() << std::endl;
		}
	}
	return c;
}


/*
get the value from the json
in: string that represent the json, a flag that check if it would be int or string
out: value
*/
std::string JsonRequestPacketDeseializer::extractValue(std::string& json, bool toInt)
{
	std::string value = "";
	if (json.find(':') != std::string::npos)
	{
		char goTo = json.find(',') != std::string::npos ? ',' : '}'; //check if it's the end of the string, and according to it deside on the right char
		value = json.substr(json.find(':') + 1, json.find(goTo) - json.find(':') - 1);

		// cuts the data string
		if (goTo == ',')
			json = json.substr(json.find(',') + 1);

		//erase spaces
		while (value[0] == ' ')
			value = value.substr(1, value.length() - 1);
		while (value[value.length() -1] == ' ')
			value = value.substr(1, value.length() - 1);
	}

	//erace " in order to get an int
	if (toInt)
		value = value.substr(1, value.length() - 2);

	return value;
}
