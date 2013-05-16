#include "stdafx.h"
#include "Game.h"
#include "Splash.h"
#include "Menu.h"

void Game::Start(void){

	if(_gameState != Uninitialized)
		return;
	_mainWindow.create(sf::VideoMode(1024,768,32),"Gravity");
	PlayerBlock *player = new PlayerBlock();
	player->load("images/block.png");
	player->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT / 2);

	_gameObjectManager.add("Block1", player);
	_gameState = Game::ShowingSplashScreen;

	while(!IsExiting()){
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting(){

		if(_gameState == Game::Exiting)
			return true;
		else
			return false;
}


sf::RenderWindow& Game::getWindow() {
	return _mainWindow;
}

const sf::Event& Game::getInput() {
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	return currentEvent;
}


void Game::GameLoop(){

	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	

		switch(_gameState){

		case Game::ShowingMenu:
			showMenu();
			break;

		case Game::ShowingSplashScreen:
			showSplashScreen();
			break;

		case Game::Playing:


			_mainWindow.clear(sf::Color(0,0,0));
			
			_gameObjectManager.updateAll(_mainWindow);
			_gameObjectManager.drawAll(_mainWindow);

			_mainWindow.display();

			if(currentEvent.type == sf::Event::Closed)
				_gameState = Game::Exiting;

			if(currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Escape) 
				showMenu();
			
			break;
		}
}

void Game::showMenu(){
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch(result) {

	case MainMenu::Exit:
		_gameState = Game::Exiting;
		break;

	case MainMenu::Play:
		_gameState = Game::Playing;
		break;
	}
}

void Game::showSplashScreen() {
	Splash splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;