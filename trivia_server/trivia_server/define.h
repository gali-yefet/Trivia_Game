#pragma once
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
#define IFACE 0;

#define PORT 3086
#define ANSWERS 4

#define ANSWERS 4


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
	GET_PERSONAL_STATS = 9,
	CLOSE_ROOM = 10,
	START_GAME = 11,
	GET_ROOM_STATE = 12,
	LEAVE_ROOM = 13
};


static const std::string questions[] = { "What is a Ransomware?" , "What are the most common types of cyber risk?", "What is WannaCry?", "What is Zero-Day?", "UDP flooding is an example of...", "Black Friday sales is an example of...", "What is MITM?", "What is Smishing?", "What is spyware?", "When was the first cyber attack?"};
static const std::string answers[] = { "Malware", "Turkey food", "Tech company in USA", "Computer application", "MITM", "Phishing", "Spyware", "Viruses", "Food Factory", "Children cry", "Cyber attack", "Cyber company", "Sunday", "The birth of Jesus", "Cyberattack Day", "Unknown hack", "Internet problems", "DDOS attack", "viruses", "ransomware", "DOS attack", "malls big sale", "Malware", "Cyber App", "an impostor", "a special attack", "cyber security company", "Ethical cyber crime", "A smooth hacker", "SMS phishing", "Cyber code", "DLL injection", "spying warning", "Virus", "A spy in war", "A malicious software", "2005", "2009", "1999", "2011"};
static const std::string rightAns[] = {"1", "2", "3", "4", "2", "1", "1", "2", "4", "3"};
