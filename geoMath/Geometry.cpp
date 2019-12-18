#include <math.h>
#include "Geometry.h"

bool isIncludeExcludingP0 ( const double &P0, const double &P1, const double &num )    // num принадлежит ли интервалу P0 - P1, исключая P0?
{
	if( P0 < P1 )
	{
		if( num > P0 && num <= P1 )
			return true;
		return false;
	}
	if( P1 < P0 )
	{
		if( num >= P1 && num < P0 )
			return true;
		return false;
	}
	return false;
}

bool isIncludeExcludingP1 ( const double &P0, const double &P1, const double &num )		// Принадлежит ли num интервалу P0 - P1, исключая P1?
{
	if( P0 < P1 )
	{
		if( num >= P0 && num < P1 )
			return true;
		return false;
	}
	if( P1 < P0 )
	{
		if( num > P1 && num <= P0 )
			return true;
	}
	return false;
}

bool isIncludeExcludingBoth ( const double &P0, const double &P1, const double &num )		// Принадлежит ли num интервалу P0 - P1, исключая P0 и P1?
{
	if( P0 < P1 )
	{
		if( num > P0 && num < P1 )
			return true;
		return false;
	}
	if( P1 < P0 )
	{
		if( num > P1 && num < P0 )
			return true;
	}
	return false;
}

bool isInclude ( const double &P0, const double &P1, const double &num )			// Принадлежит ли num интервалу P0 - P1
{
	if( P0 <= P1 )
	{
		if( num >= P0 && num <= P1 )
			return true;
		return false;
	}
	if( P1 <= P0 )
	{
		if( num >= P1 && num <= P0 )
			return true;
	}
	return false;
}


bool CrossPointLineAndPlane( Vector3D * dst, Vector3D point_plosk, Vector3D normal, Vector3D P0, Vector3D P1 ) // point_plosk - точка на плоскости, normal - нормаль к плоскости; P0, P1 - Отрезок; dst - выход
{
	Vector3D vectorP0P1 = P0-P1;
	double s = dot(normal, vectorP0P1);
	if (s == 0) return false;
	Vector3D vectorPA = point_plosk - P0;
	*dst = P0 + DotScal( vectorP0P1, dot(normal, vectorPA)/s );
	return true;
}

// Расстояние между скрещивающимеся прямыми
double twoDirectDistance(const Vector3D& A, const Vector3D& B, const Vector3D& C, const Vector3D& D)
{
	Vector3D AB = B - A;
	Vector3D CD = D - C;
	Vector3D normal = cross(AB, CD); // Нормаль к любой из двух плоскостей

	// Уравнение плоскости
	// normal.x * ( x - D.x ) + normal.y * ( y - D.y ) + normal.z * ( z - D.z ) = 0;                               
	// normal.x * x - normal.x * D.x + normal.y * y - normal.y * D.y + normal.z * z - normal.z * D.z = 0;
	double P = dot(normal, D);

	// normal.x * x + normal.y * y + normal.z * z - P = 0;
	// Нормирующий множитель
	double normMul = 1.0 / normal.Length(); //sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);

	// Нормальное уравнение плоскоти
	// normal.x * normMul * x + normal.y * normMul * y + normal.z * normMul * z - P * normMul = 0
    return fabs(normal.m_x * normMul * B.m_x + normal.m_y * normMul * B.m_y + normal.m_z * normMul * B.m_z - P * normMul );
}

// Расстояние между скрещивающимеся прямыми
double twoDirectDistanceVer2(const Vector3D& A, const Vector3D& B, const Vector3D& C, const Vector3D& D)
{
        //Vector3D AB = B - A;
        //Vector3D CD = D - C;
        //Vector3D normal = cross( AB, CD ); // Нормаль к любой из двух плоскостей
	//double len = normal.Length();
	//normal = normal * ( 1.0 / normal.Length() ); // Нормирование нормали
	/*
	// Уравнение прямой AB
	// (x1 - A.x)/AB.x = (y1 - A.y)/AB.y = (z1 - A.z)/AB.z                          
	// Уравнение прямой CD
	// (x2 - C.x)/CD.x = (y2 - C.y)/CD.y = (z2 - C.z)/CD.z
	// Уравнение нормали
	// (x1 - x2)/normal.x = (y1 - y2)/normal.y = (z1 - z2)/normal.z

	// (x1 - A.x)/AB.x = (y1 - A.y)/AB.y
	// (y1 - A.y)/AB.y = (z1 - A.z)/AB.z

	// (x2 - C.x)/CD.x = (y2 - C.y)/CD.y
	// (y2 - C.y)/CD.y = (z2 - C.z)/CD.z

	// (x1 - x2)/normal.x = (y1 - y2)/normal.y
	// (y1 - y2)/normal.y = (z1 - z2)/normal.z
	*/

	return 0;
}

double twoDirectDistanceFast( const Vector3D& A, const Vector3D& B, const Vector3D& C, const Vector3D& D ) // Расстояние между скрещивающимеся прямыми
{
	Vector3D AB = B - A;
	Vector3D CD = D - C;
	Vector3D AC = C - A;
        //Vector3D ABCD = cross(AB, CD); // векторное произведение, рез-тат которого вектор, численно равный площади основания паралелограмма, основания AB CD
        //double squard = ABCD.Length();
	double volume = dot( AC, cross(AB, CD) );
	return volume/cross(AB, CD).Length();
}

// Edge
Edge::Edge( const Vector3D *vec1, const Vector3D *vec2 )
{
	v1 = const_cast<Vector3D*>( vec1 );
	v2 = const_cast<Vector3D*>( vec2 );
	if( *v2 < *v1 )					// Вектор v1 меньше чем v2
	{
		Vector3D *tmp = v1;
		v1 = v2;
		v2 = tmp;
	}

	collinear = *v2 - *v1;
	alfa = collinear.m_x;
	beta = collinear.m_y;
	gamma = collinear.m_z;
}

bool Edge::operator != ( const Edge& other ) const
{
	if( !isBelong( other ) )
		return true;
	
	return false;
}

bool Edge::operator < ( const Edge& other ) const
{
	if( isBelong( other ) )
		return false;
	if( v1 != other.v1 )
		return ( *v1 < *other.v1 );
	return ( *v2 < *other.v2 );
}

bool Edge::GetXZ( const double &y, Vector3D& vec ) const
{
	if( beta != 0)
	{
		double x = ((y - v1->m_y) * alfa) / beta + v1->m_x;
		double z = ((y - v1->m_y) * gamma) / beta + v1->m_z;
		vec = Vector3D(x, y, z);
		Vector3D v1p = vec - *v1;
		Vector3D pv2 = *v2 - vec;
		if(dot(v1p, collinear) >= 0 && dot(pv2, collinear) > 0)
			return true;
	}
	return false;
}

bool Edge::isBelong( const Edge& other ) const
{
	Vector3D v1p1 = *other.v1 - *v1;
	Vector3D v1p2 = *other.v2 - *v1;
	if( cross( collinear, v1p1 ).Scalar() == 0 && cross( collinear, v1p2 ).Scalar() == 0 )
	{
		Vector3D p1v2 = *v2 - *other.v1;
		if( dot( v1p1, collinear ) >= 0 && dot( p1v2, collinear ) >= 0 )		// p1 внутри текущего ребра
			return true;
		Vector3D p2v2 = *v2 - *other.v2;
		if( dot( v1p2, collinear ) >= 0 && dot( p2v2, collinear ) >= 0 )		// p2 внутри текущего ребра
			return true;
		Vector3D p1v1 = *v1 - *other.v1;
		if( dot( p1v1, other.collinear) >= 0 && dot( v1p2, other.collinear ) >= 0 ) // v1 внутри другого ребра
			return true;
		Vector3D v2p2 = *other.v2 - *v2;
		if( dot( v1p2, other.collinear ) >= 0 && dot( v2p2, other.collinear ) >= 0 )
			return true;
	}

	return false;
}
//end of Edge



//Matrix4x4
Matrix4x4::Matrix4x4()
{
	m = new double[16];
}

Matrix4x4::Matrix4x4(	const double &m11, const double &m12, const double &m13, const double &m14, 
						const double &m21, const double &m22, const double &m23, const double &m24, 
						const double &m31, const double &m32, const double &m33, const double &m34,
						const double &m41, const double &m42, const double &m43, const double &m44	)
{
	m = new double[16];
	m[0]  =	 m11;
	m[1]  =	 m12;
	m[2]  =	 m13;
	m[3]  =	 m14;

	m[4]  =	 m21;
	m[5]  =	 m22;
	m[6]  =	 m23;
	m[7]  =	 m24;

	m[8]  =	 m31;
	m[9]  =	 m32;
	m[10] =	 m33;
	m[11] =	 m34;

	m[12] =	 m41;
	m[13] =	 m42;
	m[14] =	 m43;
	m[15] =	 m44;
}

Matrix4x4::Matrix4x4(const Vector3D &vec1, const Vector3D &vec2, const Vector3D &vec3)
{
	m[0] = vec1.m_x;
	m[1] = vec2.m_x;
	m[2] = vec3.m_x;
	m[3] = 0;

	m[4] = vec1.m_y;
	m[5] = vec2.m_y;
	m[6] = vec3.m_y;
	m[7] = 0;

	m[8] = vec1.m_z;
	m[9] = vec2.m_z;
	m[10]= vec3.m_z;
	m[11]= 0;

	m[12]= 0;
	m[13]= 0;
	m[14]= 0;
	m[15]= 1;
}

Matrix4x4::Matrix4x4(double *m)
{
	m = new double[16];
	for( int i = 0; i<16; i++ )
		this->m[i] = m[i];
}

Vector4D Matrix4x4::operator*( const Vector4D &vec ) const
{
	Vector4D result;

	result.x = m[0] * vec.x + m[1] * vec.y + m[2] * vec.z + m[3] * vec.w;
	result.y = m[4] * vec.x + m[5] * vec.y + m[6] * vec.z + m[7] * vec.w;
	result.z = m[8] * vec.x + m[9] * vec.y + m[10]* vec.z + m[11]* vec.w;
	result.w = m[12]* vec.x + m[13]* vec.y + m[14]* vec.z + m[15]* vec.w;

	return result;
}

Matrix4x4::~Matrix4x4()
{
	delete [] m;
}

double* Matrix4x4::getPtr()
{
	return m;
}
//end of Matrix4x4

// Ray
Ray::Ray( const Vector3D& pos, const Vector3D& dir )
{
	position = pos;
	direction = dir;
}
// end of Ray

// Poly
Poly::Poly()
{
	v.resize(0);
	normal = 0;
}

Poly::Poly( const Vector3D *v1, const Vector3D *v2, const Vector3D *v3, const Vector3D *normal )
{
	v.resize( 3 );
	v[0] = const_cast<Vector3D*>( v1 );
	v[1] = const_cast<Vector3D*>( v2 );
	v[2] = const_cast<Vector3D*>( v3 );
	this->normal = const_cast<Vector3D*>( normal );
}

Poly::Poly( Vector3D **v, const int &n, const Vector3D *normal )
{
	this->v.resize(n);
	for( auto i = 0; i < n; i++ )
		this->v[i] = const_cast<Vector3D*>( v[i] );

	this->normal = const_cast<Vector3D*>(normal );
}

Poly::Poly( Vector3D **v, Vector2D *tex, const int &n, const Vector3D *normal )
{
	this->v.resize( n );
	this->tex.resize( n );
	for( auto i = 0; i < n; i++ )
	{
		this->v[i] = const_cast<Vector3D*>( v[i] );
		this->tex[i] = tex[i];
	}

	this->normal = const_cast<Vector3D*>(normal );
}

Poly::Poly( const Poly& other )
{
    //v = other.v;
    v.resize( other.v.size());
    for( size_t i = 0; i < v.size(); i++ )
        v[i] = other.v[i];
    normal = other.normal;
}

Poly::~Poly()
{
}

Poly& Poly::operator = ( const Poly& other )
{
    v = other.v;
    for( size_t i = 0; i < v.size(); i++ )
        v[i] = other.v[i];
    normal = other.normal;
    return *this;
}

bool Poly::operator != ( const Poly& other ) const
{
    if( v.size() != other.v.size() )
        return true;

    for( size_t i = 0; i < v.size(); i++ )
    {
        if( v[i] != other.v[i] )
            return true;
    }

    return ( normal != other.normal );
}

bool Poly::operator== ( const Poly& other ) const
{
    return !( operator != (other) );
}

bool Poly::operator < ( const Poly& other ) const
{
    if( v.size() != other.v.size() )
        return ( v.size() < other.v.size() );

    for ( size_t i = 0; i < v.size(); i++ )
    {
        if( v[i] != other.v[i] )
            return ( v[i] < other.v[i] );
    }
	
    return ( normal < other.normal );
}

bool Poly::isBelongY( const double &y ) const
{
        for( size_t i = 0; i < v.size() - 1; i++ )
	{
		Vector3D *v1, *v2;
		v1 = v[i];
		if( i < v.size()-1 )
			v2 = v[i+1];
		else
			v2 = v[0];
		Edge edg( v1, v2 );
		Vector3D vec;
		if( edg.GetXZ( y, vec ) )
			return true;
	}
	return false;
}

bool Poly::HalfIntersectRay( Vector3D &dst, const Vector3D &P0, const Vector3D &P1 )
{
	Vector3D vectorP0P1 = P1-P0;
	double s = dot(*normal, vectorP0P1);
	if( s == 0)
		return false;

	Vector3D a = *v[v.size()-1] - P0;
	Vector3D b = *v[0] - P0;
	Vector3D vec = cross( a, b );
	double ip = dot( vectorP0P1, vec );

	if( ip == 0.0 )
		return false;

	double sum1, sum2;
	sum1 = ip;
	sum2 = fabs(ip);

        for( size_t i = 0; i < v.size()-1; i++ )
	{
		a = *v[i] - P0;
		b = *v[i+1] - P0;
		vec = cross( a, b );
		ip = dot( vectorP0P1, vec );
		if( ip == 0.0 )
			return false;
		sum1 += ip;
		sum2 += fabs(ip);
	}

	if( fabs(sum1) >= sum2 )
	{
		Vector3D vectorPA = *v[0] - P0;
		dst = P0 + DotScal( vectorP0P1, dot(*normal, vectorPA)/s );
		return true;
	}
	return false;
}

bool Poly::HalfIntersectRay( const Vector3D &P0, const Vector3D &P1 )
{
	Vector3D vectorP0P1 = P1-P0;
	double s = dot(*normal, vectorP0P1);
	if( s == 0)
		return false;

	Vector3D a = *v[v.size()-1] - P0;
	Vector3D b = *v[0] - P0;
	Vector3D vec = cross( a, b );
	double ip = dot( vectorP0P1, vec );

	if( ip == 0.0 )
		return false;

	double sum1, sum2;
	sum1 = ip;
	sum2 = fabs(ip);

        for( size_t i = 0; i < v.size()-1; i++ )
	{
		a = *v[i] - P0;
		b = *v[i+1] - P0;
		vec = cross( a, b );
		ip = dot( vectorP0P1, vec );
		if( ip == 0.0 )
			return false;
		sum1 += ip;
		sum2 += fabs(ip);
	}

	if( fabs(sum1) >= sum2 )
		return true;

	return false;
}

bool Poly::FullIntersectRay( Vector3D &dst, const Vector3D &P0, const Vector3D &P1 )
{
	
	Vector3D vectorP0P1 = P1-P0;
	double s = dot(*normal, vectorP0P1);
	if( s == 0)
		return false;
	Vector3D a = *v[v.size()-1] - P0;
	Vector3D b = *v[0] - P0;
	Vector3D vec = cross( a, b );
	double ip = dot( vectorP0P1, vec );
	double sum1, sum2;
	sum1 = ip;
	sum2 = fabs(ip);
        for( size_t i = 0; i < v.size()-1; i++ )
	{
		a = *v[i] - P0;
		b = *v[i+1] - P0;
		vec = cross( a, b );
		ip = dot( vectorP0P1, vec );
		sum1 += ip;
		sum2 += fabs(ip);
	}

	if( fabs(sum1) >= sum2 )
	{
		Vector3D vectorPA = *v[0] - P0;
		dst = P0 + DotScal( vectorP0P1, dot(*normal, vectorPA)/s );
		return true;
	}
	return false;
}

bool Poly::FullIntersectRay( const Vector3D &P0, const Vector3D &P1 )
{
	Vector3D vectorP0P1 = P1-P0;
	double s = dot(*normal, vectorP0P1);
	if( s == 0)
		return false;
	Vector3D a = *v[v.size()-1] - P0;
	Vector3D b = *v[0] - P0;
	Vector3D vec = cross( a, b );
	double ip = dot( vectorP0P1, vec );
	double sum1, sum2;
	sum1 = ip;
	sum2 = fabs(ip);
        for( size_t i = 0; i < v.size()-1; i++ )
	{
		a = *v[i] - P0;
		b = *v[i+1] - P0;
		vec = cross( a, b );
		ip = dot( vectorP0P1, vec );
		sum1 += ip;
		sum2 += fabs(ip);
	}

	if( fabs(sum1) >= sum2 )
		return true;

	return false;
}

bool Poly::HalfIntersect( Vector3D &dst, const Vector3D &P0, const Vector3D &P1 )
{
	Vector3D vectorP0P1 = P1-P0;
	double s = dot(*normal, vectorP0P1);
	if( s == 0)
		return false;

	Vector3D a = *v[v.size()-1] - P0;
	Vector3D b = *v[0] - P0;
	Vector3D vec = cross( a, b );
	double ip = dot( vectorP0P1, vec );

	if( ip == 0.0 )
		return false;

	double sum1, sum2;
	sum1 = ip;
	sum2 = fabs(ip);

        for( size_t i = 0; i < v.size()-1; i++ )
	{
		a = *v[i] - P0;
		b = *v[i+1] - P0;
		vec = cross( a, b );
		ip = dot( vectorP0P1, vec );
		if( ip == 0.0 )
			return false;
		sum1 += ip;
		sum2 += fabs(ip);
	}

	if( fabs(sum1) >= sum2 )
	{
		Vector3D vectorPA = *v[0] - P0;
		dst = P0 + DotScal( vectorP0P1, dot(*normal, vectorPA)/s );
		Vector3D P0dst = dst - P0;
		Vector3D dstP1 = P1 - dst;
		if( dot( P0dst, vectorP0P1 ) >=0 && dot( dstP1, vectorP0P1 ) >=0 )
			return true;
	}
	return false;
}

bool Poly::HalfIntersect( const Vector3D &P0, const Vector3D &P1 )
{
	Vector3D vectorP0P1 = P1-P0;
	double s = dot(*normal, vectorP0P1);
	if( s == 0)
		return false;

	Vector3D a = *v[v.size()-1] - P0;
	Vector3D b = *v[0] - P0;
	Vector3D vec = cross( a, b );
	double ip = dot( vectorP0P1, vec );

	if( ip == 0.0 )
		return false;

	double sum1, sum2;
	sum1 = ip;
	sum2 = fabs(ip);

        for( size_t i = 0; i < v.size()-1; i++ )
	{
		a = *v[i] - P0;
		b = *v[i+1] - P0;
		vec = cross( a, b );
		ip = dot( vectorP0P1, vec );
		if( ip == 0.0 )
			return false;
		sum1 += ip;
		sum2 += fabs(ip);
	}

	if( fabs(sum1) >= sum2 )
	{
		Vector3D vectorPA = *v[0] - P0;
		Vector3D dst = P0 + DotScal( vectorP0P1, dot(*normal, vectorPA)/s );
		Vector3D P0dst = dst - P0;
		Vector3D dstP1 = P1 - dst;
		if( dot( P0dst, vectorP0P1 ) >=0 && dot( dstP1, vectorP0P1 ) >= 0 )
			return true;
	}
	return false;
}

bool Poly::HalfIntersectExcludingP0( Vector3D &dst, const Vector3D &P0, const Vector3D &P1 )
{
	Vector3D vectorP0P1 = P1-P0;
	double s = dot(*normal, vectorP0P1);
	if( s == 0)
		return false;

	Vector3D a = *v[v.size()-1] - P0;
	Vector3D b = *v[0] - P0;
	Vector3D vec = cross( a, b );
	double ip = dot( vectorP0P1, vec );
	if( ip == 0.0 )
		return false;
	double sum1, sum2;
	sum1 = ip;
	sum2 = fabs(ip);
        for( size_t i = 0; i < v.size()-1; i++ )
	{
		a = *v[i] - P0;
		b = *v[i+1] - P0;
		vec = cross( a, b );
		ip = dot( vectorP0P1, vec );
		if( ip == 0.0 )
			return false;
		sum1 += ip;
		sum2 += fabs(ip);
	}
	if( fabs(sum1) >= sum2 )
	{
		Vector3D vectorPA = *v[0] - P0;
		dst = P0 + DotScal( vectorP0P1, dot(*normal, vectorPA)/s );
		Vector3D P0dst = dst - P0;
		Vector3D dstP1 = P1 - dst;
		if( dot( P0dst, vectorP0P1 ) > 0 && dot( dstP1, vectorP0P1 ) >=0 )
			return true;
	}
	return false;
}

bool Poly::HalfIntersectExcludingP0( const Vector3D &P0, const Vector3D &P1 )
{
	Vector3D vectorP0P1 = P1-P0;
	double s = dot(*normal, vectorP0P1);
	if( s == 0)
		return false;
	Vector3D a = *v[v.size()-1] - P0;
	Vector3D b = *v[0] - P0;
	Vector3D vec = cross( a, b );
	double ip = dot( vectorP0P1, vec );
	if( ip == 0.0 )
		return false;
	double sum1, sum2;
	sum1 = ip;
	sum2 = fabs(ip);
        for( size_t i = 0; i < v.size()-1; i++ )
	{
		a = *v[i] - P0;
		b = *v[i+1] - P0;
		vec = cross( a, b );
		ip = dot( vectorP0P1, vec );
		if( ip == 0.0 )
			return false;
		sum1 += ip;
		sum2 += fabs(ip);
	}
	if( fabs(sum1) >= sum2 )
	{
		Vector3D vectorPA = *v[0] - P0;
		Vector3D dst = P0 + DotScal( vectorP0P1, dot(*normal, vectorPA)/s );
		Vector3D P0dst = dst - P0;
		Vector3D dstP1 = P1 - dst;
		if( dot( P0dst, vectorP0P1 ) > 0 && dot( dstP1, vectorP0P1 ) >=0 )
			return true;
	}
	return false;
}

bool Poly::FullIntersect( Vector3D &dst, const Vector3D &P0, const Vector3D &P1 )
{
	Vector3D vectorP0P1 = P1-P0;
	double s = dot(*normal, vectorP0P1);
	if( s == 0)
		return false;
	Vector3D a = *v[v.size()-1] - P0;
	Vector3D b = *v[0] - P0;
	Vector3D vec = cross( a, b );
	double ip = dot( vectorP0P1, vec );
	double sum1, sum2;
	sum1 = ip;
	sum2 = fabs(ip);
        for( size_t i = 0; i < v.size()-1; i++ )
	{
		a = *v[i] - P0;
		b = *v[i+1] - P0;
		vec = cross( a, b );
		ip = dot( vectorP0P1, vec );
		sum1 += ip;
		sum2 += fabs(ip);
	}

	if( fabs(sum1) >= sum2 )
	{
		Vector3D vectorPA = *v[0] - P0;
		dst = P0 + DotScal( vectorP0P1, dot(*normal, vectorPA)/s );
		Vector3D P0dst = dst - P0;
		Vector3D dstP1 = P1 - dst;
		if( dot( P0dst, vectorP0P1 ) >=0 && dot( dstP1, vectorP0P1 ) >=0 )
			return true;
	}
	return false;
}

bool Poly::FullIntersect( const Vector3D &P0, const Vector3D &P1 )
{
	Vector3D vectorP0P1 = P1-P0;
	double s = dot(*normal, vectorP0P1);
	if( s == 0)
		return false;
	Vector3D a = *v[v.size()-1] - P0;
	Vector3D b = *v[0] - P0;
	Vector3D vec = cross( a, b );
	double ip = dot( vectorP0P1, vec );
	double sum1, sum2;
	sum1 = ip;
	sum2 = fabs(ip);
        for( size_t i = 0; i < v.size()-1; i++ )
	{
		a = *v[i] - P0;
		b = *v[i+1] - P0;
		vec = cross( a, b );
		ip = dot( vectorP0P1, vec );
		sum1 += ip;
		sum2 += fabs(ip);
	}

	if( fabs(sum1) >= sum2 )
	{
		/*
		Vector3D vectorPA = *v[0] - P0;
		Vector3D vectorPB = P1 - *v[0];
		double dot1 = dot( vectorPA, *normal );
		if( dot( vectorPB, *normal ) > 0 )
			return ( dot1 < 0 );
		else
			return ( dot1 > 0 );
			*/
		Vector3D vectorPA = *v[0] - P0;
		Vector3D dst = P0 + DotScal( vectorP0P1, dot(*normal, vectorPA)/s );
		Vector3D P0dst = dst - P0;
		Vector3D dstP1 = P1 - dst;
		if( dot( P0dst, vectorP0P1 ) >=0 && dot( dstP1, vectorP0P1 ) >=0 )
			return true;
	}
	return false;
}

bool Poly::FullIntersectExcludingP0( Vector3D &dst, const Vector3D &P0, const Vector3D &P1 )
{
	Vector3D vectorP0P1 = P1-P0;
	double s = dot(*normal, vectorP0P1);
	if( s == 0)
		return false;
	Vector3D a = *v[v.size()-1] - P0;
	Vector3D b = *v[0] - P0;
	Vector3D vec = cross( a, b );
	double ip = dot( vectorP0P1, vec );
	double sum1, sum2;
	sum1 = ip;
	sum2 = fabs(ip);
        for( size_t i = 0; i < v.size()-1; i++ )
	{
		a = *v[i] - P0;
		b = *v[i+1] - P0;
		vec = cross( a, b );
		ip = dot( vectorP0P1, vec );
		sum1 += ip;
		sum2 += fabs(ip);
	}

	if( fabs(sum1) >= sum2 )
	{
		Vector3D vectorPA = *v[0] - P0;
		dst = P0 + DotScal( vectorP0P1, dot(*normal, vectorPA)/s );
		Vector3D P0dst = dst - P0;
		Vector3D dstP1 = P1 - dst;
		if( dot( P0dst, vectorP0P1 ) > 0 && dot( dstP1, vectorP0P1 ) >=0 )
			return true;
	}
	return false;
}

bool Poly::FullIntersectExcludingP0( const Vector3D &P0, const Vector3D &P1 )
{
	Vector3D vectorP0P1 = P1-P0;
	double s = dot(*normal, vectorP0P1);
	if( s == 0)
		return false;
	Vector3D a = *v[v.size()-1] - P0;
	Vector3D b = *v[0] - P0;
	Vector3D vec = cross( a, b );
	double ip = dot( vectorP0P1, vec );
	double sum1, sum2;
	sum1 = ip;
	sum2 = fabs(ip);
        for( size_t i = 0; i < v.size()-1; i++ )
	{
		a = *v[i] - P0;
		b = *v[i+1] - P0;
		vec = cross( a, b );
		ip = dot( vectorP0P1, vec );
		sum1 += ip;
		sum2 += fabs(ip);
	}
	if( fabs(sum1) >= sum2 )
	{
		Vector3D vectorPA = *v[0] - P0;
		Vector3D dst = P0 + DotScal( vectorP0P1, dot(*normal, vectorPA)/s );
		Vector3D P0dst = dst - P0;
		Vector3D dstP1 = P1 - dst;
		if( dot( P0dst, vectorP0P1 ) > 0 && dot( dstP1, vectorP0P1 ) >=0 )
			return true;
	}
	return false;
}

bool Poly::FullIntersectExcludingBoth( Vector3D &dst, const Vector3D &P0, const Vector3D &P1 )
{
	Vector3D vectorP0P1 = P1-P0;
	double s = dot(*normal, vectorP0P1);
	if( s == 0)
		return false;
	Vector3D a = *v[v.size()-1] - P0;
	Vector3D b = *v[0] - P0;
	Vector3D vec = cross( a, b );
	double ip = dot( vectorP0P1, vec );
	double sum1, sum2;
	sum1 = ip;
	sum2 = fabs(ip);
        for( size_t i = 0; i < v.size()-1; i++ )
	{
		a = *v[i] - P0;
		b = *v[i+1] - P0;
		vec = cross( a, b );
		ip = dot( vectorP0P1, vec );
		sum1 += ip;
		sum2 += fabs(ip);
	}
	if( fabs(sum1) >= sum2 )
	{
		Vector3D vectorPA = *v[0] - P0;
		dst = P0 + DotScal( vectorP0P1, dot(*normal, vectorPA)/s );
		Vector3D P0dst = dst - P0;
		Vector3D dstP1 = P1 - dst;
		if( dot( P0dst, vectorP0P1 ) > 0 && dot( dstP1, vectorP0P1 ) > 0 )
			return true;
	}
	return false;
}

bool Poly::FullIntersectExcludingBoth( const Vector3D &P0, const Vector3D &P1 )
{
	Vector3D vectorP0P1 = P1-P0;
	double s = dot(*normal, vectorP0P1);
	if( s == 0)
		return false;
	Vector3D a = *v[v.size()-1] - P0;
	Vector3D b = *v[0] - P0;
	Vector3D vec = cross( a, b );
	double ip = dot( vectorP0P1, vec );
	double sum1, sum2;
	sum1 = ip;
	sum2 = fabs(ip);
        for( size_t i = 0; i < v.size()-1; i++ )
	{
		a = *v[i] - P0;
		b = *v[i+1] - P0;
		vec = cross( a, b );
		ip = dot( vectorP0P1, vec );
		sum1 += ip;
		sum2 += fabs(ip);
	}
	if( fabs(sum1) >= sum2 )
	{
		Vector3D vectorPA = *v[0] - P0;
		Vector3D dst = P0 + DotScal( vectorP0P1, dot(*normal, vectorPA)/s );
		Vector3D P0dst = dst - P0;
		Vector3D dstP1 = P1 - dst;
		if( dot( P0dst, vectorP0P1 ) > 0 && dot( dstP1, vectorP0P1 ) >0 )
			return true;
	}
	return false;
}

bool Poly::isPositive( const Vector3D &P0, const Vector3D &P1 )
{
	Vector3D vectorP0P1 = P1-P0;
	double ip = dot( vectorP0P1, *normal );
	return ip > 0;
}

void Poly::AddEdge( const Edge &edge )
{
	edges.insert( const_cast<Edge*>(&edge) );
}
// end of Poly

