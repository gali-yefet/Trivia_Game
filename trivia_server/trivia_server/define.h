#pragma once
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
#define IFACE 0;

#define PORT 3086

enum codes {
	ERROR_CODE = 0,
	SIGN_CODE = 1,
	LOGIN_CODE = 2,
	CREATE_ROOM = 3,
	GET_ROOMS = 4,
	GET_PLAYERS_IN_ROOM = 5,
	JOIN_ROOM = 6,
	GET_STATISTICS = 7,
	LOGOUT = 8
};
