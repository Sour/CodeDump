#include "stdafx.h"
#include "PlayerBlock.h"
#include "Game.h"


PlayerBlock::PlayerBlock() : _velocity(0), _maxVelocity(1000.0f) {
	load("images/block.png");
	assert(isLoaded());

	getSprite().setOrigin(getSprite().getLocalBounds().width / 2, getSprite().getLocalBounds().height / 2);
}

PlayerBlock::~PlayerBlock() {
}

void PlayerBlock::update(float elapsedTime) {

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
		_velocity -= 3.0f;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_velocity += 3.0f;

	if(_velocity > _maxVelocity)
		_velocity = _maxVelocity;

	if(_velocity < -_maxVelocity)
		_velocity = -_maxVelocity;

	sf::Vector2f pos = this->getPosition();

	if(pos.x < getSprite().getLocalBounds().width / 2 || 
		pos.x > (Game::SCREEN_WIDTH - getSprite().getLocalBounds().width / 2)) 
			_velocity = -_velocity;

	getSprite().move(_velocity * elapsedTime, 0);
}

void PlayerBlock::draw(sf::RenderWindow& renderWindow) {
	VisibleGameObject::draw(renderWindow);
}

float PlayerBlock::getVelocity() const {
	return _velocity;
}

