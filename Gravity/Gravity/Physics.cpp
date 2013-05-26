#include "stdafx.h"
#include "Physics.h"

float Physics::Distance(sf::Vector2f a, sf::Vector2f b )
{
	return sqrt( ( ( a.x - b.x ) * ( a.x - b.x ) ) + ( ( a.y - b.y ) * ( a.y - b.y ) ) );
}

bool Physics::RectvsRect( Rect a, Rect b )
{
	if ( a.max.x < b.min.x || a.min.x > b.max.x ) return false;
	if ( a.max.y < b.min.y || a.min.y > b.max.y ) return false;
	return true;
}

bool Physics::CirclevsCircle( Circle a, Circle b )
{
	return ( a.radius + b.radius ) < Distance( a.position, b.position );
}

bool Physics::CirclevsRect( Circle a, Rect b )
{
	if(b.max.x < a.radius || b.min.x < a.radius ) return false;
	if(b.max.y < a.radius || b.min.y < a.radius ) return false;
	return true;
}