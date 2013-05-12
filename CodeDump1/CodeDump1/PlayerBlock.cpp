#include "stdafx.h"
#include "PlayerBlock.h"
#include "Game.h"

#define PI 3.14159265

PlayerBlock::PlayerBlock() : _velocity(0), _maxVelocity(750.0f), _elapsedTimeSinceStart(0.0f), _angle(0.01f) {
	load("images/block.png");
	assert(isLoaded());

	getSprite().setOrigin(getSprite().getLocalBounds().width / 2, getSprite().getLocalBounds().height / 2);
}

PlayerBlock::~PlayerBlock() {
}

void PlayerBlock::update(sf::RenderWindow& renderWindow, float elapsedTime) {


	if(elapsedTime != _elapsedTimeSinceStart) {
		_velocity *= .9997;
		std::cout << _velocity << std::endl;
		_elapsedTimeSinceStart += elapsedTime;
	}
	
	
	sf::Vector2f pos = this->getPosition();

	if(sf::Mouse::getPosition(renderWindow).x > pos.x + (getSprite().getLocalBounds().width / 2))
		_velocity += 1.0f;
		
	if(sf::Mouse::getPosition(renderWindow).x < pos.x - (getSprite().getLocalBounds().width / 2))
		_velocity -= 1.0f;

	if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
		_velocity = 0;

	if(_velocity > _maxVelocity)
		_velocity = _maxVelocity;

	if(_velocity < -_maxVelocity)
		_velocity = -_maxVelocity;


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

void PlayerBlock::setRotation() {

}

float PlayerBlock::linearVelocityX(float angle) {
	angle -= 90;
	if(angle < 0) angle = 360 + angle;
		return (float)std::cos( angle * ( PI / 180.0f ));

}

float PlayerBlock::linearVelocityY(float angle) {
	angle -= 90;
	if(angle < 0) angle = 360 + angle;
		return (float)std::sin( angle * ( PI / 180.0f ));
}
