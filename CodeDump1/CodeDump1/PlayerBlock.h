#pragma once
#include "VisibleGameObject.h"

class PlayerBlock :
	public VisibleGameObject {

public:
	PlayerBlock();
	~PlayerBlock();

	void update(sf::RenderWindow& renderWindow, float elapsedTime);
	void draw(sf::RenderWindow& renderWindow);

	float getVelocityX() const;
	float getVelocityY() const;


private:
	float _angle;
	float _xVelocity;
	float _yVelocity;
	float _maxVelocity;
	float _elapsedTimeSinceStart;

	float linearVelocityX(float angle);
	float linearVelocityY(float angle);

};

