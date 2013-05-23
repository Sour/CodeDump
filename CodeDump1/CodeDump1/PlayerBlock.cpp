#include "stdafx.h"
#include "PlayerBlock.h"
#include "Game.h"

#define PI 3.14159265
#define G 50
#define THRUST 125

PlayerBlock::PlayerBlock() : _velocity(0,0), _maxVelocity(750.0f) {
	load("images/block.png");
	assert(isLoaded());

	getSprite().setOrigin(getSprite().getLocalBounds().width / 2, getSprite().getLocalBounds().height / 2);
	getSprite().setScale(.5,.5);
}

PlayerBlock::~PlayerBlock() {
}

void PlayerBlock::update(sf::RenderWindow& renderWindow, float elapsedTime) {

	sf::Vector2f pos = this->getPosition();
	sf::Vector2f force;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
		getSprite().setPosition(1024 / 2, 15);


	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		linearVelocity(elapsedTime);
	

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		_velocity *= .9998f;
	

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		getSprite().rotate(-.05f);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		getSprite().rotate(.05f);
	}



	if(pos.x < getSprite().getLocalBounds().width / 2 || 
		pos.x > (Game::SCREEN_WIDTH - getSprite().getLocalBounds().width / 2)) 
		_velocity.x = -_velocity.x;
	
	if(pos.y < getSprite().getLocalBounds().height / 2 || 
		pos.y > (Game::SCREEN_HEIGHT - getSprite().getLocalBounds().height / 2))
		_velocity.y = -_velocity.y;

	if( _velocity.x > _maxVelocity )
		_velocity.x = _maxVelocity;

	if( _velocity.x < -_maxVelocity )
		_velocity.x = -_maxVelocity;

	if( _velocity.y > _maxVelocity )
		_velocity.y = _maxVelocity;

	if( _velocity.y < -_maxVelocity )
		_velocity.y = -_maxVelocity;
	
	gravity(elapsedTime);
	lift(elapsedTime);
	getSprite().move(_velocity * elapsedTime);
}

void PlayerBlock::draw(sf::RenderWindow& renderWindow) {
	VisibleGameObject::draw(renderWindow);
}

void PlayerBlock::linearVelocity(float dt) {

	double angle = getSprite().getRotation() * PI / 180;

	_force.x = std::cos( angle ) * dt * THRUST;
	_force.y = std::sin( angle ) * dt * THRUST;

	_velocity += _force;
}

void PlayerBlock::lift(float dt)
{
	float angle, cl, vAng, sAng;

	
	sAng = std::abs(getSprite().getRotation() - 360);
	vAng = atan2 (_velocity.y, _velocity.x) * 180 / PI;

	if(vAng < 0) vAng += 360;
	vAng = std::abs(vAng - 360);

	angle = sAng - vAng;
	cl = -angle / 100;

}


void PlayerBlock::gravity(float dt) {
	_velocity.y += G * dt;
}

void PlayerBlock::drag(float dt) {

	float totalVelocity = std::sqrt( ( _velocity.x * _velocity.x ) + ( _velocity.y * _velocity.y ) );
	float fd = .5 * (1.2 * 0.0310809502) * totalVelocity * .25 * 11;
	

}