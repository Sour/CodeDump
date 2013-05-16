#pragma once
#include "VisibleGameObject.h"

class PlayerBlock :

	public VisibleGameObject {
		
	struct State {
		float x;
		float v;
	};

	static struct Derivative {
		float dx;
		float dv;
	};

public:
	PlayerBlock();
	~PlayerBlock();

	void update(sf::RenderWindow& renderWindow, float elapsedTime);
	void draw(sf::RenderWindow& renderWindow);
	

private:
	
	

	sf::Vector2f _velocity;
	sf::Vector2f _force;

	float _maxVelocity;
	float _elapsedTimeSinceStart;

	void linearVelocity();
	Derivative evaluate(const State &initial, float t, float dt, const Derivative &d);
};

