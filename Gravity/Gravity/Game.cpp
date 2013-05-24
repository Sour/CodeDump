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
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);

	switch(_gameState)
	{
	case Game::Exiting:
		break;
	case Game::Uninitialized:
		break;
	case Game::Playing:
		break;
	default:
		break;
	}

}

bool Game::exiting()
{
	if(_gameState == Game::Exiting)
		return true;
	return false;
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;