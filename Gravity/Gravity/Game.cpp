#include "stdafx.h"
#include "Game.h"

void Game::start(void)
{
	if(_gameState = Uninitialized)
		return;

	while(!exiting)
		gameLoop();

}

void Game::gameLoop()
{

}

bool Game::exiting()
{
	if(_gameState == Exiting)
		return true;
	return false;
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;