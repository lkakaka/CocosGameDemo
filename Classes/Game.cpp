#include "Game.h"

Game* Game::g_game = new Game();

Game* Game::getInstance() {
	return Game::g_game;
}