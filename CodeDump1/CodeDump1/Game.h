#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "PlayerBlock.h"
#include "GameObjectManager.h"


class Game {

public:
	static void Start();

	static sf::RenderWindow& getWindow();

	const sf::Event& getInput();

	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;

private:
	static bool IsExiting();
	static void GameLoop();
	static void showSplashScreen();
	static void showMenu();

	enum GameState { Uninitialized, Playing, ShowingSplashScreen, ShowingMenu, Exiting };

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	static GameObjectManager _gameObjectManager;
};