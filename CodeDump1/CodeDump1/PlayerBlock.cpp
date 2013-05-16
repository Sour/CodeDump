#include "stdafx.h"
#include "PlayerBlock.h"
#include "Game.h"

#define PI 3.14159265
#define G 9.81
#define thrust 50

PlayerBlock::PlayerBlock() : _velocity(0,0), _maxVelocity(750.0f) {
	load("images/block.png");
	assert(isLoaded());

	getSprite().setOrigin(getSprite().getLocalBounds().width / 2, getSprite().getLocalBounds().height / 2);
}

PlayerBlock::~PlayerBlock() {
}

void PlayerBlock::update(sf::RenderWindow& renderWindow, float elapsedTime) {

	sf::Vector2f pos = this->getPosition();
	sf::Vector2f force;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
		getSprite().setPosition(1024 / 2, 15);


	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		linearVelocity();
		_velocity += _force;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		linearVelocity();
		_velocity *= .9998f;
	}

	if(pos.x < getSprite().getLocalBounds().width / 2 || 
		pos.x > (Game::SCREEN_WIDTH - getSprite().getLocalBounds().width / 2)) 
		_velocity.x = -_velocity.x;
	
	if(pos.y < getSprite().getLocalBounds().height / 2 || 
		pos.y > (Game::SCREEN_HEIGHT - getSprite().getLocalBounds().height / 2))
		_velocity.y = -_velocity.y;

	if( _velocity.x > _maxVelocity )
		_velocity.x = _maxVelocity;

	if( _velocity.y > _maxVelocity )
		_velocity.y = _maxVelocity;
	
	gravity(elapsedTime);
	getSprite().move(_velocity * elapsedTime);
}

void PlayerBlock::draw(sf::RenderWindow& renderWindow) {
	VisibleGameObject::draw(renderWindow);
}

void PlayerBlock::linearVelocity() {

	double angle = getSprite().getRotation() * PI / 180;
	_force.x = std::cos( angle );
	_force.y = std::sin( angle );
}


void PlayerBlock::gravity(float dt) {
	_velocity.y += G * dt;
}