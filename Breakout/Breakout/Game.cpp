#include "stdafx.h"

void Game::start(void)
{
	if(_gameState != Uninitialized)
		return;

	_mainWindow.create(VideoMode(640, 480, 32), "Breakout");

	

	_gameState = Game::Playing;

	while(!isExiting())
		gameLoop();
	_mainWindow.close();
}

bool Game::isExiting()
{
	if(_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::gameLoop()
{
	Player *player1 = new Player();

	GameObjectManager _gameObjectManager;
	player1->init(Vector2f(60,30), Color::Black);
	player1->setPosition(Vector2f(320,400));

	_gameObjectManager.add("Player1",player1);


	switch(_gameState)
	{
	case Game::Playing:
		Event currentEvent;
		while(_mainWindow.pollEvent(currentEvent))
		{
			_mainWindow.clear(Color::White);	
			_gameObjectManager.drawAll(_mainWindow);
			_mainWindow.display();

			if(currentEvent.type == Event::Closed)
				_gameState = Game::Exiting;

			if(currentEvent.type == Event::KeyPressed && currentEvent.key.code == Keyboard::Escape)
				_gameState = Game::Exiting;
		}
		break;
	}
}

Game::gameState Game::_gameState = Uninitialized;
RenderWindow Game::_mainWindow;
