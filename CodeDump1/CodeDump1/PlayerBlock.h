#pragma once
#include "VisibleGameObject.h"

class PlayerBlock :

	public VisibleGameObject {

public:
	PlayerBlock();
	~PlayerBlock();

	void update(sf::RenderWindow& renderWindow, float elapsedTime);
	void draw(sf::RenderWindow& renderWindow);
	
private:
	
	sf::Vector2f _velocity;
	sf::Vector2f _force;

	float _maxVelocity;

	void linearVelocity(float dt);
	void lift(float dt);
	void gravity(float dt);
	void drag(float dt);
	void resistance(float dt);

};

