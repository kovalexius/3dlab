#ifndef __VECTOR3D__H
#define __VECTOR3D__H

//------------------------------------------------------------------------------
//------------------------------ class Vector3D --------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//! Класс Vector3D представляет трехмерный вектор и 
//! методы для работы с ним.
/*! */
//------------------------------------------------------------------------------
class Vector3D
{
public:
	Vector3D();

	//! Конструктор класса, принимающий параметры: x координата, y координата и z координата
	Vector3D(double x, double y, double z);

	//! Конструктор копирования
	Vector3D( const Vector3D& other);

	//! Оператор присваивания
	Vector3D& operator = ( const Vector3D& other );

	//! Оператор неравно, возвращает true если текущий объект не равен other
	bool operator != ( const Vector3D& other ) const;

	//! Оператор равно, возвращает true если текущий объект равен other
	bool operator == ( const Vector3D& other ) const;

	//! Оператор меньше, возвращает true если текущий объект меньше other
	/*! Сначала вектора сравниваются по x, потом по y, потом по z */
	bool operator < ( const Vector3D& other ) const;

	//! Оператор математического сложения векторов
	Vector3D operator - ( const Vector3D& other ) const;

	//! Оператор математического вычитания векторов
	Vector3D operator + ( const Vector3D& other ) const;

	//! Масштабирование вектора на скалярную величину
	Vector3D operator * ( const double& num ) const;

	//! Деление вектора на скалярную величину
	Vector3D operator / ( const double& num ) const;

	//! Получить скаляр вектора, то есть результат скалярного умножения на самого себя
	/*! Скаляр вектора является длиной вектора в квадрате. */
	double Scalar() const;

	//! Получить длину вектора
	double Length() const;

	//! Отмасштабировать вектор
	Vector3D Scaling(const double& _rhs) const;

	Vector3D Normalize() const;

	double m_x;
	double m_y;
	double m_z;
};

// Скалярное умножение векторов
double dot(const Vector3D& v1, const Vector3D& v2);

Vector3D DotScal(const Vector3D& a, double num);

// Векторное уимножение Cross Product
Vector3D cross(const Vector3D& v1, const Vector3D& v2);

#endif