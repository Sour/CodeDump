#pragma once
#include "VisibleGameObject.h"

class PlayerBlock :
	public VisibleGameObject {

public:
	PlayerBlock();
	~PlayerBlock();

	void update(float elapsedTime);
	void draw(sf::RenderWindow& renderWindow);

	float getVelocity() const;

private:
	float _velocity;
	float _maxVelocity;
};