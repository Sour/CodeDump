#pragma once
#include "stdafx.h"

class GameObjectManager
{
public:	
	GameObjectManager();
	~GameObjectManager();

	void add(std::string name, GameObject* gameObject);
	void remove(std::string name);

	int getObjectCount() const;

	GameObject* get(std::string name) const;

	void drawAll(RenderWindow& renderWindow);

private:
	map<std::string, GameObject*> _gameObjects;
	
	struct GameObjectDeallocator
	{
		void operator()(const pair<std::string,GameObject*> & p) const
		{
			delete p.second;
		}
	};
};