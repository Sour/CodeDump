#pragma once

#include "stdafx.h"

class Physics 
{
private:

public:
	
	struct Rect 
	{
		sf::Vector2f min;
		sf::Vector2f max;
	};

	struct Circle
	{
		sf::Vector2f position;
		float radius;
	};

	bool RectvsRect( Rect a, Rect b );
	bool CirclevsCircle( Circle a, Circle b );
	bool CirclevsRect( Circle a, Rect b );
		
	//void ResolveCollision( Object a, Object b );

	float Distance( sf::Vector2f a, sf::Vector2f b );
};