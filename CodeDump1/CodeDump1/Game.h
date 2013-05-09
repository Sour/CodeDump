#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Game {

public:
	static void Start();

private:
	static bool IsExiting();
	static void GameLoop();

	static void showSplashScreen();

	enum GameState { Uninitialized, Playing, ShowingSplashScreen, Exiting };

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
};