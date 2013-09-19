#pragma once
#include "stdafx.h"

using namespace sf;

class Game
{
public:
	static void start();

private:
	static bool isExiting();
	static void gameLoop();

	enum gameState { Uninitialized, Paused, Playing, Exiting };

	static gameState _gameState;
	static RenderWindow _mainWindow;
};