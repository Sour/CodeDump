#include "stdafx.h"
#include "PlayerBlock.h"
#include "Game.h"

#define PI 3.14159265

struct State {
	float x;
	float v;
};

struct Derivative {
	float dx;
	float dv;
};

float acceleration(const State &state, float t) {
	const float k = 10;
	const float b = 1;
	return -k * state.x - b * state.v;
}

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

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
		getSprite().setPosition(1024/2, 768 / 2);


	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		State state; 
		state.x = getSprite().getPosition().x;
		state.v = 0;

		float t = 0;
		float dt = elapsedTime;
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

Derivative evaluate(const State &initial, float t, float dt, const Derivative &d) {
	State state;
	state.x = initial.x + d.dx * dt;
	state.v = initial.v + d.dv * dt;

	Derivative output;
	output.dx = state.v;
	output.dv = acceleration(state, t+dt);
	return output;
}

void integrate(State &state, float t, float dt){
	Derivative a = evaluate(state, t, 0.0f, Derivative());
	Derivative b = evaluate(state, t, dt*0.5f, a);
	Derivative c = evaluate(state, t, dt*0.5f, b);
	Derivative d = evaluate(state, t, dt, c);

	const float dxdt = 1.0f/6.0f * (a.dx + 2.0f * (b.dx + c.dx) + d.dx);
	const float dvdt = 1.0f / 6.0f * (a.dv + 2.0f * (b.dv + c.dv) + d.dv);

	state.x = state.x + dxdt * dt;
	state.v = state.v + dvdt * dt;

}