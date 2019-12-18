#include "vector4d.h"


// Vector4D
Vector4D::Vector4D()
{
}

Vector4D::Vector4D( const double &x, const double &y, const double &z, const double &w )
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4D::Vector4D( const Vector4D &other )
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

Vector3D Vector4D::xyz() const
{
	return Vector3D( x, y, z );
}
// end of Vector4D

