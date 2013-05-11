#include "stdafx.h"
#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject() : _isLoaded(false){
}

VisibleGameObject::~VisibleGameObject() {
}

void VisibleGameObject::load(std::string filename) {
	if(_texture.loadFromFile(filename) == false) {
		_filename = "";
		_isLoaded = false;
	}else{
		_filename = filename;
		_sprite.setTexture(_texture);
		_isLoaded = true;
	}
}

void VisibleGameObject::draw(sf::RenderWindow& window){
	if(_isLoaded)
		window.draw(_sprite);
}

void VisibleGameObject::update(float elapsedTime) {

}

sf::Vector2f VisibleGameObject::getPosition() const{
	if(_isLoaded)
		return _sprite.getPosition();
	return sf::Vector2f();
}

sf::Sprite& VisibleGameObject::getSprite() {
	return _sprite;
}

void VisibleGameObject::setPosition(float x, float y) {
	if(_isLoaded)
		_sprite.setPosition(x, y);
}

bool VisibleGameObject::isLoaded() const {
	return _isLoaded;
}