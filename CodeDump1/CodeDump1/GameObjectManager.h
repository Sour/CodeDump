#pragma once
#include "VisibleGameObject.h"

class GameObjectManager {

public:
	GameObjectManager();
	~GameObjectManager();

	void add(std::string name, VisibleGameObject* gameObject);
	void remove(std::string name);
	void updateAll(sf::RenderWindow& renderWindow);

	int getObjectCount() const;
	
	VisibleGameObject* Get(std::string name) const;

	void drawAll(sf::RenderWindow& renderWindow);

private:
	std::map<std::string, VisibleGameObject*> _gameObject;

	sf::Clock clock;

	struct GameObjectDeallocator {
		void operator() (const std::pair<std::string, VisibleGameObject*> & p) const {
			delete p.second;
		}
	};
};