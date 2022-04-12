#pragma once
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
#define IFACE 0;

#define PORT 3086

enum codes {
	SIGN_CODE = 5,
	LOGIN_CODE = 6,
	ERROR_CODE = 7
};