#include "stdafx.h"


GameObject::GameObject()
{
	_isLoaded = false;
}

GameObject::~GameObject()
{
}

void GameObject::init(Vector2f size, Color color)
{
	rectObject.setSize(size);
	rectObject.setFillColor(color);
	_isLoaded = true;
}

void GameObject::draw(RenderWindow &_mainWindow)
{
	if(_isLoaded)
		_mainWindow.draw(rectObject);
}

void GameObject::setPosition(Vector2f pos)
{
	if(_isLoaded)
	rectObject.setPosition(pos);
}

void GameObject::move(Vector2f speed)
{
	if(_isLoaded)
	rectObject.move(speed);
}

FloatRect GameObject::getGlobalbounds()
{
	if(_isLoaded)
	return rectObject.getGlobalBounds();
}