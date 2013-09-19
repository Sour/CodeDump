#include "stdafx.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	for_each(_gameObjects.begin(), _gameObjects.end() ,GameObjectDeallocator());
}

void GameObjectManager::add(string name, GameObject* gameObject)
{
	_gameObjects.insert(pair<string,GameObject*>(name,gameObject));
}

void GameObjectManager::remove(string name)
{
	map<string, GameObject*>::iterator results = _gameObjects.find(name);
	if(results != _gameObjects.end())
	{
		delete results -> second;
		_gameObjects.erase(results);
	}
}

GameObject* GameObjectManager::get(string name) const
{
	map<string, GameObject*>::const_iterator results = _gameObjects.find(name);
	if(results == _gameObjects.end())
	{
		return NULL;
	}
	return results->second;
}

int GameObjectManager::getObjectCount() const
{
	return _gameObjects.size();
}

void GameObjectManager::drawAll(RenderWindow& _mainWindow)
{
	map<string, GameObject*>::const_iterator itr = _gameObjects.begin();
	while(itr != _gameObjects.end())
	{
		itr->second->draw(_mainWindow);
		itr++;
	}
}