#pragma once
#include "stdafx.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void init(Vector2f size, Color color);

	virtual void draw(RenderWindow &_mainWindow);

	virtual void setPosition(Vector2f pos);

	virtual void move(Vector2f speed);

	virtual FloatRect getGlobalbounds();



private:
	bool _isLoaded;
	RectangleShape rectObject;
};