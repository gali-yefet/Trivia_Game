#pragma once
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
#define IFACE 0;

#define PORT 3086

enum codes {
	ERROR_CODE = 0,
	SIGN_CODE = 1,
	LOGIN_CODE = 2,
	LOGOUT = 3,
	CREATE_ROOM = 4,
	GET_ROOMS = 5,
	GET_PLAYERS_IN_ROOM = 6,
	JOIN_ROOM = 7,
	GET_HIGH_SCORE = 8,
	GET_PERSONAL_STATS = 9
};
