#include "vector2d.h"


// Vector2D
Vector2D::Vector2D()
{
	x = 0;
	y = 0;
}

Vector2D::Vector2D( double x, double y )
{
	this->x = x;
	this->y = y;
}

Vector2D::Vector2D( const Vector2D& other )
{
	x = other.x;
	y = other.y;
}

Vector2D& Vector2D::operator= ( const Vector2D& other )
{
	x = other.x;
	y = other.y;
	return *this;
}

bool Vector2D::operator!=( const Vector2D& other ) const
{
	return ( x != other.x || y != other.y );
}

bool Vector2D::operator==( const Vector2D& other ) const
{
	return !( x != other.x || y != other.y );
}

bool Vector2D::operator<( const Vector2D& other ) const
{
	if( x != other.x )
		return ( x < other.x );
	return ( y < other.y );
}
// end of Vector2D

