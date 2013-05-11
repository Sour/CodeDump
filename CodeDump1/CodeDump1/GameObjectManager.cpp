#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"


GameObjectManager::GameObjectManager(){
}

GameObjectManager::~GameObjectManager(){
	std::for_each(_gameObject.begin(), _gameObject.end(), GameObjectDeallocator());
}

void GameObjectManager::add(std::string name, VisibleGameObject* gameObject) {
	_gameObject.insert(std::pair<std::string, VisibleGameObject*> (name, gameObject));
}

void GameObjectManager::remove(std::string name) {
	std::map<std::string, VisibleGameObject*>::iterator results = _gameObject.find(name);
	if(results != _gameObject.end()) {
		delete results -> second;
		_gameObject.erase(results);
	}
}

void GameObjectManager::updateAll() {
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObject.begin();

	float timeDelta = clock.restart().asSeconds();

	while(itr != _gameObject.end()) {
		itr->second->update(timeDelta);
		itr++;
	}

}

VisibleGameObject* GameObjectManager::Get(std::string name) const {
	std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObject.find(name);
	if(results == _gameObject.end())
		return NULL;
	return results->second;
}

int GameObjectManager::getObjectCount() const {
	return _gameObject.size();
}

void GameObjectManager::drawAll(sf::RenderWindow& renderWindow) {
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObject.begin();
	while (itr != _gameObject.end()) {
		itr->second->draw(renderWindow);
		itr++;
	}
}
