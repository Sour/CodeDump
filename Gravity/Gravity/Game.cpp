#include "stdafx.h"
#include "Game.h"

void Game::start(void)
{
	if(_gameState != Game::Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1024,768,32),"Gravity");
	_gameState = Game::Playing;

	while(!exiting())
		gameLoop();

	_mainWindow.close();
}

bool Game::exiting()
{
	if(_gameState == Game::Exiting)
		return true;
	return false;
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

		_mainWindow.clear(sf::Color(0,0,0));
		_mainWindow.display();

		if(currentEvent.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				_gameState = Game::Exiting;

		break;
	default:
		break;
	}
	_mainWindow.display();
}



Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;