#include "stdafx.h"
#include "Game.h"

void Game::start(void)
{
	if(_gameState != Game::Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(500,501,32),"Gravity");
	_mainWindow.clear(sf::Color(0,0,0));
	_mainWindow.setVerticalSyncEnabled(true);
	_mainWindow.display();

	_gameState = Game::Draw;
	
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

void Game::drawGrid()
{
	int min = 0;
	int max = 500;
	
	sf::VertexArray line(sf::Lines, 2);


	for(int it = 0; it <= 10; it++)
	{
		
		line[0].position = sf::Vector2f(min, it * 50);
		line[1].position = sf::Vector2f(max, it * 50);
		_mainWindow.draw(line);

	}

	for(int it = 0; it <= 10; it++)
	{
		
		line[0].position = sf::Vector2f(it * 50, min);
		line[1].position = sf::Vector2f(it * 50, max);
		_mainWindow.draw(line);

	}
	line[0].position = sf::Vector2f(1, min);
	line[1].position = sf::Vector2f(1, max);
	_mainWindow.draw(line);
	_gameState = Game::Playing;
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
		if(currentEvent.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				_gameState = Game::Exiting;
		break;
	case Game::Draw:
		drawGrid();
		break;
	default:
		break;
	}
	_mainWindow.display();
	
}



Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;