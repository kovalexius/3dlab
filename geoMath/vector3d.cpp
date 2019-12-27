#include "vector3d.h"
#include <cmath>
#include <limits>
#include <iomanip>

double dot(const Vector3D& v1, const Vector3D& v2)		// Скалярное умножение векторов
{
	return v1.m_x*v2.m_x + v1.m_y*v2.m_y + v1.m_z*v2.m_z;
}

Vector3D DotScal(const Vector3D& _a, double num)
{
    return Vector3D(_a.m_x*num, _a.m_y*num, _a.m_z*num);
}

Vector3D cross(const Vector3D& v1, const Vector3D& v2)	// Векторное уимножение Cross Product
{
	Vector3D result;
	result.m_x = v1.m_y * v2.m_z - v1.m_z * v2.m_y;
	result.m_y = v1.m_z * v2.m_x - v1.m_x * v2.m_z;
	result.m_z = v1.m_x * v2.m_y - v1.m_y * v2.m_x;
	return result;
}

// Vector3D
Vector3D::Vector3D()
{
	m_x=0;
	m_y=0;
	m_z=0;
}

Vector3D::Vector3D(double _x, double _y, double _z)
{
	m_x = _x;
	m_y = _y;
	m_z = _z;
}

Vector3D::Vector3D(const Vector3D& other)
{
	m_x = other.m_x;
	m_y = other.m_y;
	m_z = other.m_z;
}

Vector3D& Vector3D::operator = (const Vector3D& other)
{
	m_x = other.m_x;
	m_y = other.m_y;
	m_z = other.m_z;

	return *this;
}

bool Vector3D::operator!= (const Vector3D& other) const
{
	if(m_x != other.m_x || m_y != other.m_y || m_z != other.m_z)
		return true;
	return false;
}

bool Vector3D::operator== (const Vector3D& other) const
{
	return !(operator!=(other));
}

bool Vector3D::operator< (const Vector3D& other) const
{
	if(m_x != other.m_x)
		return (m_x < other.m_x);
	else if (m_y != other.m_y)
		return (m_y < other.m_y);
	else if (m_z != other.m_z)
		return (m_z < other.m_z);
	
	return false;
}

Vector3D Vector3D::operator- (const Vector3D& other) const
{
	return Vector3D(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
}

Vector3D Vector3D::operator+(const Vector3D& other) const
{
	return Vector3D(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
}

Vector3D Vector3D::operator*(const double& num) const
{
	return Vector3D(m_x*num, m_y*num, m_z*num);
}

Vector3D Vector3D::operator/(const double& num) const
{
	return Vector3D(m_x/num, m_y/num, m_z/num);
}

double Vector3D::Scalar() const
{
	return m_x*m_x + m_y*m_y + m_z*m_z;
}

double Vector3D::Length() const
{
	return sqrt(Scalar());
}

Vector3D Vector3D::Scaling(const double& _rhs) const
{
	return Vector3D(m_x*_rhs, m_y*_rhs, m_z*_rhs);
}

Vector3D Vector3D::Normalize() const
{
	return Scaling(1.0/Length());
}

std::ostream& operator<<(std::ostream& _os, const Vector3D& _vec)
{
	_os << std::setprecision(std::numeric_limits<double>::digits10 + 1) << "x: " << _vec.m_x << " y: " << _vec.m_y << " z: " << _vec.m_z;
	return _os;
}

void setMaximum(Vector3D& _vec)
{
	_vec.m_x = std::numeric_limits<double>::max();
    _vec.m_y = std::numeric_limits<double>::max();
    _vec.m_z = std::numeric_limits<double>::max();
}
void setMinimum(Vector3D& _vec)
{
	_vec.m_x = std::numeric_limits<double>::min();
    _vec.m_y = std::numeric_limits<double>::min();
    _vec.m_z = std::numeric_limits<double>::min();
}
// end of Vector3D