#pragma once

#include "stdafx.h"


class Game 
{
public:
	void start();

private:
	static void gameLoop();
	static bool exiting();

	enum GameState { Uninitialized, Playing, Exiting };

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;



};