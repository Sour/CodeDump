#include "stdafx.h"
#include "PlayerBlock.h"
#include "Game.h"

#define PI 3.14159265

PlayerBlock::PlayerBlock() : _xVelocity(0), _yVelocity(0), _maxVelocity(750.0f), _elapsedTimeSinceStart(0.0f), _angle(0.01f) {
	load("images/block.png");
	assert(isLoaded());

	getSprite().setOrigin(getSprite().getLocalBounds().width / 2, getSprite().getLocalBounds().height / 2);
}

PlayerBlock::~PlayerBlock() {
}

void PlayerBlock::update(sf::RenderWindow& renderWindow, float elapsedTime) {


	if(elapsedTime != _elapsedTimeSinceStart) {
		_xVelocity *= .9997;
		_yVelocity *= .9991;
		_elapsedTimeSinceStart += elapsedTime;
	}
		
	sf::Vector2f pos = this->getPosition();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		getSprite().rotate(-.05f);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		getSprite().rotate(.05f);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		_xVelocity += 1.0f;
		_yVelocity += 1.0f;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		_xVelocity -= 1.0f;
		_yVelocity -= 1.0f;
	}

	if(_xVelocity > _maxVelocity || _yVelocity > _maxVelocity){
		_xVelocity = _maxVelocity;
		_yVelocity = _maxVelocity;
	}

	if(_xVelocity < -_maxVelocity || _yVelocity < -_maxVelocity) {
		_xVelocity =  -_maxVelocity;
		_yVelocity = -_maxVelocity;
	}

	if(pos.x < getSprite().getLocalBounds().width / 2 || 
		pos.x > (Game::SCREEN_WIDTH - getSprite().getLocalBounds().width / 2)) {
			_xVelocity = -_xVelocity;
	}
	getSprite().move((linearVelocityX(getSprite().getRotation()) * _xVelocity) * elapsedTime, 
					 (linearVelocityY(getSprite().getRotation()) * -_xVelocity) * elapsedTime);
}

void PlayerBlock::draw(sf::RenderWindow& renderWindow) {
	VisibleGameObject::draw(renderWindow);
}

float PlayerBlock::getVelocityX() const {
	return _xVelocity;
}

float PlayerBlock::getVelocityY() const {
	return _yVelocity;
}

float PlayerBlock::linearVelocityX(float angle) {
	return (float)std::cos( angle );
}

float PlayerBlock::linearVelocityY(float angle) {
	return (float)std::sin( angle );
}
