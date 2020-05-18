#pragma once
#include <string>

#define GAME_INSTACNE Game::getInstance()

class MasterRole {
public:
	std::string account;
	int role_id;
	std::string role_name;
};


class Game{
private:
	static Game* g_game;
public:
	MasterRole masterRole;
	static Game* getInstance();
	
};

