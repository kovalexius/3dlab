﻿//------------------------------------------------------------------------------
//! @author Edited by: Ковалев А.Г.
//!
/*! @file

    @brief
			Классы описывающие различные геометрические примитивы,
			А также глобальные методы оперирующие с объектами этих классов
    @details  */
//------------------------------------------------------------------------------
#ifndef Geometry_H
#define Geometry_H
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#include <set>
#include <map>
#include <vector>

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------ class Vector2D --------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Класс Vector2D представляет двухмерный вектор и 
//! методы для работы с ним.
/*! */
//------------------------------------------------------------------------------
class Vector2D
{
public:
	Vector2D();
	//! Конструктор класса, принимающий параметры: x координата и y координата
	Vector2D( double x, double y );
	//! Конструктор копирования
	Vector2D( const Vector2D& other );
	//! Оператор присваивания
	Vector2D& operator = ( const Vector2D& other );

	//! Оператор неравно, возвращает true если текущий объект не равен other
	bool operator != ( const Vector2D& other ) const;
	//! Оператор равно, возвращает true если текущий объект равен other
	bool operator == ( const Vector2D& other ) const;
	//! Оператор меньше, возвращает true если текущий объект меньше other
	/*! Сначала вектора сравниваются по x, потом по y. */
	bool operator < ( const Vector2D& other ) const;
	
	double x;
	double y;
};


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

	double x;
	double y;
	double z;
};


//------------------------------------------------------------------------------
//------------------------------ class Vector4D --------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//! Класс Vector4D представляет четырехмерный вектор.
//! Выступает как хранилище для некоторых функций.
/*! */
//------------------------------------------------------------------------------
class Vector4D
{
public:
	Vector4D();
	//! Конструктор класса, принимающий параметры: x координата, y координата, z координата и w координата
	Vector4D( const double &x, const double &y, const double &z, const double &w );
	//! Конструктор копирования
	Vector4D( const Vector4D &other );
	//! Получить трехмерную составляющую четырехмерного вектора
	Vector3D xyz( ) const;

	double x;
	double y;
	double z;
	double w;
};


//------------------------------------------------------------------------------
//------------------------------ class Matrix4x4 -------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//! Класс Matrix4x4 представляет матрицу 4 столбца 4 строки.
//! Выступает как хранилище для некоторых функций OpenGL.
/*! */
//------------------------------------------------------------------------------
class Matrix4x4
{
public:
	Matrix4x4();
	//! Конструктор со всеми 16 параметрами матрицы
	Matrix4x4(  const double &m11, const double &m12, const double &m13, const double &m14, 
							const double &m21, const double &m22, const double &m23, const double &m24, 
							const double &m31, const double &m32, const double &m33, const double &m34,
							const double &m41, const double &m42, const double &m43, const double &m44 );
	//! Конструктор принимающий вектора в кач-ве столбцов матрицы
	Matrix4x4( const Vector4D &vec1, const Vector4D &vec2, const Vector4D &vec3, const Vector4D& vec4 );
	Matrix4x4( const Vector3D &vec1, const Vector3D &vec2, const Vector3D &vec3 );
	//! Конструктор, прнимающий массив из 16 элементов
	Matrix4x4( double *m );
	~Matrix4x4(  );
	//! Умножение матрицы на вектор
	Vector4D operator*( const Vector4D &vec ) const;
	//! Получить указатель на область памяти где хранятся данные матрицы
	/*! Используется для некоторых функций OpenGL */
	double* getPtr();
private:
	double *m;
};

class Ray
{
public:
	Ray( const Vector3D& pos, const Vector3D& dir );
	Vector3D position;
	Vector3D direction;
};


//------------------------------------------------------------------------------
//------------------------------ class Edge ------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//! Класс Edge представляет данные и методы для работы с ребрами
//! как графическими примитивами.
//! Ребро описывается двумя трехмерными векторами Vector3D
/*! */
//------------------------------------------------------------------------------
class Edge
{
public:
	//! Конструктор принимающий начальную и конечную вершину ребра
	/*! В v1 помещается меньший вектор, в v2 - больший */
	Edge( const Vector3D *v1, const Vector3D *v2 );
	//! Оператор неравно, возвращает true если текущий объект неравен other
	/*! Ребра считаются равны если они лежат на одной прямой
			и соприкасаются друг с другом. В остальных случаях - неравны */
	bool operator != ( const Edge &other ) const;
	//! Оператор меньше
	/*! Сначала сравнивается точка v1, потом v2 */
	bool operator < (  const Edge &other ) const;

	//! Получить точку на ребре при заданном значении y
	/*! Вход:  y - Значение по высоте
			Выход: vec - результирующая точка
	*		@return	 Возвращает true если такая точка на ребре может существовать, иначе - false	*/
	bool GetXZ( const double &y, Vector3D& vec ) const;
	//! Лежат ли ребра на одной прямой и соприкасаются друг с другом
	bool isBelong( const Edge & other ) const;
	Vector3D *v1;
	Vector3D *v2;
private:
	//! Вектор, коллинеарный, то есть параллельный ребру
	Vector3D collinear;
	//! координата x коллинеарного вектора, в математике называется alfa ибо коэффициент
	double alfa;
	//! координата y коллинеарного вектора, в математике называется beta ибо коэффициент
	double beta;
	//! координата z коллинеарного вектора, в математике называется гамма ибо коэффициент
	double gamma;
};

class Poly
{
public:
	Poly();
	Poly( const Vector3D *v1, const Vector3D *v2, const Vector3D *v3, 
				const Vector3D *normal );
	Poly( Vector3D **v, const int &n, const Vector3D *normal );
	Poly( Vector3D **v, Vector2D* tex, const int &n, const Vector3D *normal );
	Poly( const Poly& other );
	virtual ~Poly();
	Poly& operator = ( const Poly& other );
	bool operator != ( const Poly& other ) const;
	bool operator == ( const Poly& other ) const;
	bool operator < ( const Poly& other ) const;
	
	//! Определяет, пересекает ли данный полигон плоскость y
	bool isBelongY( const double &y ) const;

	//! Найти пересечение луча с полигоном
	/*! Пересечение исключает ребра полигонов.
			Вход: P0 - первая точка Vector3D луча
						P1 - вторая точка Vector3D луча
			Выход:	dst - точка перечечения
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool HalfIntersectRay( Vector3D &dst, const Vector3D &P0, const Vector3D &P1 ); // Проверка на пересечение прямой без ребер треугольника
	//! Определить было ли пересечение луча с полигоном.
	/*! Пересечение исключает ребра полигонов. Обнаруживает только факт пересечения без нахождения точки пересечения.
			Вход: P0 - первая точка Vector3D луча
						P1 - вторая точка Vector3D луча
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool HalfIntersectRay( const Vector3D &P0, const Vector3D &P1);
	//! Найти пересечение луча с полигоном
	/*! Пересечение засчитывается, если луч прошел полигон объекта а также если попал на ребро полигона.
			Вход: P0 - первая точка Vector3D луча
						P1 - вторая точка Vector3D луча
			Выход:	dst - точка перечечения
	*		@return	 Возвращает true если было перечение, иначе false	*/
	bool FullIntersectRay( Vector3D &dst, const Vector3D &P0, const Vector3D &P1 ); // Проверка на пересечение прямой с реберами треугольника
	//! Определить было ли пересечение луча с полигоном.
	/*! Пересечение засчитывается, если луч прошел полигон объекта а также если попал на ребро полигона.
			Обнаруживает только факт пересечения без возврата точки пересечения.
	Вход: P0 - первая точка Vector3D луча
				P1 - вторая точка Vector3D луча
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool FullIntersectRay( const Vector3D &P0, const Vector3D &P1 );
	//! Найти пересечение отрезка с полигоном
	/*! Пересечение исключает ребра полигонов.
			Вход: P0 - первая точка Vector3D луча
						P1 - вторая точка Vector3D луча
			Выход:	dst - точка перечечения
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool HalfIntersect( Vector3D &dst, const Vector3D &P0, const Vector3D &P1 );	// Проверка на пересечение отрезка без ребер треугольника
	//! Определить было ли пересечение отрезка с полигоном.
	/*! Пересечение исключает ребра полигонов. Обнаруживает только факт пересечения без нахождения точки пересечения.
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool HalfIntersect( const Vector3D &P0, const Vector3D &P1 );
	//! Найти пересечение отрезка с полигоном
	/*! Пересечение засчитывается, если отрезок прошел полигон объекта а также если попал на ребро полигона.
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
			Выход:	dst - точка перечечения
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool FullIntersect( Vector3D &dst, const Vector3D &P0, const Vector3D &P1 );	// Проверка на пересечение отрезка с реберами треугольника
	//! Определить было ли пересечение отрезка с полигоном.
	/*! Пересечение засчитывается, если отрезок прошел полигон объекта а также если попал на ребро полигона.
			Обнаруживает только факт пересечения без нахождения точки пересечения.
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool FullIntersect( const Vector3D &P0, const Vector3D &P1 );
	//! Найти пересечение отрезка с полигоном
	/*! Пересечение исключает ребра полигонов и начало отрезка P0, т.е. если точка P0 лежит в полигоне, пересечение не засчитывается.
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
			Выход:	dst - точка перечечения
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool HalfIntersectExcludingP0( Vector3D &dst, const Vector3D &P0, const Vector3D &P1 );	// Проверка на пересечение отрезка без ребер треугольника исключая начальную точку отрезка
	//! Определить было ли пересечение отрезка с полигоном
	/*! Пересечение исключает ребра полигонов и начало отрезка P0, т.е. если точка P0 лежит в полигоне, пересечение не засчитывается.
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool HalfIntersectExcludingP0( const Vector3D &P0, const Vector3D &P1 );
	//! Найти пересечение отрезка с полигоном
	/*! Пересечение засчитывается, если отрезок прошел полигон объекта, а также если попал на ребро полигона.
			Пересечение исключает начало отрезка P0, т.е. если точка P0 лежит в полигоне, пересечение не засчитывается.
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
			Выход:	dst - точка перечечения
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool FullIntersectExcludingP0( Vector3D &dst, const Vector3D &P0, const Vector3D &P1 );	// Проверка на пересечение отрезка с реберами треугольника исключая начальную точку отрезка
	//! Определить было ли пересечение отрезка с полигоном
	/*! Пересечение засчитывается, если отрезок прошел полигон объекта, а также если попал на ребро полигона.
			Пересечение исключает начало отрезка P0, т.е. если точка P0 лежит в полигоне, пересечение не засчитывается.
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool FullIntersectExcludingP0( const Vector3D &P0, const Vector3D &P1 );
	//! Найти пересечение отрезка с полигоном
	/*! Пересечение засчитывается, если отрезок прошел полигон объекта, а также если попал на ребро полигона.
			Пересечение исключает начало отрезка P0, и конец отрезка P1.
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
			Выход:	dst - точка перечечения
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool FullIntersectExcludingBoth( Vector3D &dst, const Vector3D &P0, const Vector3D &P1 );
	//! Определить есть ли пересечение отрезка с полигоном
	/*! Пересечение засчитывается, если отрезок прошел полигон объекта, а также если попал на ребро полигона.
			Пересечение исключает начало отрезка P0, и конец отрезка P1.
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool FullIntersectExcludingBoth( const Vector3D &P0, const Vector3D &P1 );
	//! Определить падает ли Вектор P0P1 снаружи полигона или изнутри
	/*! Вход: P0 - начальная точка вектора
						P1 - конечная точка вектора
	*		@return	 Возвращает true если падает изнутри, false если снаружи	*/
	bool isPositive( const Vector3D &P0, const Vector3D &P1 );
	
	//! Привязывает ребро edge к полигону
	void AddEdge( const Edge &edge );

	std::vector< Vector3D *> v;
	//! Текстурные координаты
	std::vector< Vector2D > tex;
	Vector3D *normal;
	std::set<Edge*> edges;
};

//! Векторное уимножение Cross Product
Vector3D cross( const Vector3D& v1, const Vector3D& v2 );	

//! point_plosk - точка на плоскости, normal - нормаль к плоскости; P0, P1 - Отрезок; dst - выход
bool CrossPointLineAndPlane( Vector3D * dst, Vector3D point_plosk, Vector3D normal, Vector3D P0, Vector3D P1 );

//! Скалярное умножение вектора на число (масштабирование)
Vector3D DotScal(const Vector3D &a, double num);

//! Расстояние между скрещивающимеся прямыми
double twoDirectDistance( const Vector3D& A, const Vector3D& B, const Vector3D& C, const Vector3D& D ); 

//! Расстояние между скрещивающимеся прямыми
double twoDirectDistanceVer2( const Vector3D& A, const Vector3D& B, const Vector3D& C, const Vector3D& D );
//! Расстояние между скрещивающимеся прямыми. Альтернативная версия
double twoDirectDistanceFast( const Vector3D& A, const Vector3D& B, const Vector3D& C, const Vector3D& D );


#endif
