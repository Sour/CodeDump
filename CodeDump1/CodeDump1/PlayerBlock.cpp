#include "stdafx.h"
#include "PlayerBlock.h"
#include "Game.h"

#define PI 3.14159265

PlayerBlock::PlayerBlock() : _velocity(0,0), _maxVelocity(750.0f), _elapsedTimeSinceStart(0.0f) {
	load("images/block.png");
	assert(isLoaded());

	getSprite().setOrigin(getSprite().getLocalBounds().width / 2, getSprite().getLocalBounds().height / 2);
}

PlayerBlock::~PlayerBlock() {
}

void PlayerBlock::update(sf::RenderWindow& renderWindow, float elapsedTime) {

	sf::Vector2f pos = this->getPosition();
	sf::Vector2f force;

	if(elapsedTime != _elapsedTimeSinceStart) {
		if( ((getSprite().getLocalBounds().height / 2) + getSprite().getPosition().y) < 768 ) 
			_velocity.y += .25;
		
		
		_velocity.x *= .9997;
		_velocity.y *= .9991;
		_elapsedTimeSinceStart += elapsedTime;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
		getSprite().setPosition(1024/2, 768 / 2);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		getSprite().rotate(-.05f);/*
		updateVelocity();*/
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		getSprite().rotate(.05f);/*
		updateVelocity();*/
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		linearVelocity();
		_velocity += _force;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		linearVelocity();
		_velocity -= _force;
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

void PlayerBlock::updateVelocity() {

	int itr = 1;
	double angle = getSprite().getRotation();

	while(getSprite().getRotation() > 90) {
		angle -= 90;
		itr++;
	}

	switch(itr) {
	case 1:
		
	_force.x = std::cos( angle );
	_force.y = 1 * std::sin( angle );


	case 2:
		
	_force.x = -std::cos( angle );
	_force.y = 1 * std::sin( angle );


	case 3:
		
	_force.x = -std::cos( angle );
	_force.y = -1 * std::sin( angle );


	case 4:

	_force.x = std::cos( angle );
	_force.y = -1 * std::sin( angle );


	default:
		break;
	}
	

	double totalVelocity = sqrt( (_velocity.x*_velocity.x) + (_velocity.y*_velocity.y) );

	std::cout << "x: " <<  _velocity.x << " y: " << _velocity.y << " Angle: " << angle << " tv: " << totalVelocity << std::endl;
	angle = 90 - angle;
	_velocity.x = ( totalVelocity * std::sin( angle ));
	_velocity.y = ( totalVelocity * std::cos( angle ));
	
	std::cout << "2x: " <<  _velocity.x << " y: " << _velocity.y << " Angle: " << angle << " tv: " << totalVelocity << std::endl;


}