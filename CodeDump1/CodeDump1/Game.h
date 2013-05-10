#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "PlayerBlock.h"

class Game {

public:
	static void Start();

private:
	static bool IsExiting();
	static void GameLoop();

	static void showSplashScreen();
	static void showMenu();

	enum GameState { Uninitialized, Playing, ShowingSplashScreen, ShowingMenu, Exiting };

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	static PlayerBlock _player1;
};