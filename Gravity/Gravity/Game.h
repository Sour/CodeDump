#pragma once

#include "stdafx.h"


class Game 
{
public:
	static void start();

private:
	static void gameLoop();
	static bool exiting();
	static void drawGrid();

	enum GameState { Uninitialized, Playing, Exiting, Draw };

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;



};