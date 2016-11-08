﻿//------------------------------------------------------------------------------
//! @author Edited by: Ковалев А.Г.
//!
/*! @file

    @brief
     Класс MeshObject собирает поверхность из контейнера map< Vector3D*, shared_ptr<set<shared_ptr<Poly>>> >,
		 удаляя соответсвующие записи из этого контейнера. Класс хранит информацию о геометрии объекта и о непосредственных
		 геометрических примитивах актуальных для определения обхода объекта влево или вправо. Также обладает методами, определяющими
		 пересечение луча или отрезка с данным объектом
    @details  */
//------------------------------------------------------------------------------
#ifndef MESHOBJECT_H
#define MESHOBJECT_H
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#include <queue>
#include <memory>

#include "Geometry.h"

class MeshObject
{
public:
	//! Конструктор класса, принимающий параметры: контейнер map< Vector3D*, shared_ptr<set<shared_ptr<Poly>>> >
	/*! Конструктор класса, принимающий параметры: контейнер, в качестве ключа которого используется вершина, 
			в качестве значения список полигонов. 
			Конструктор удаляет из контейнера те записи которые соответствуют геометрии данного объекта. */
  MeshObject( std::map< Vector3D*, std::shared_ptr<std::set<std::shared_ptr<Poly>>> > &vecToTri );
	//! Хранилище вершин
	std::set< Vector3D > points;
	//! Хранилище нормалей
	std::set< Vector3D > normals;
	//! Хранилище полигонов объекта
	std::set< std::shared_ptr<Poly> > tris;
};


//------------------------------------------------------------------------------
//---------------------------- class MeshObstacle  -------------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Класс MeshObstacle определяет объект, хранит геометрию, предоставляет 
//! методы для определения пересечений с ним.
/*! */
//------------------------------------------------------------------------------
class MeshObstacle
{
public:
	//! Конструктор класса, принимающий параметры: контейнер map< Vector3D*, shared_ptr<set<shared_ptr<Poly>>> >
	/*! Конструктор класса, принимающий параметры: контейнер, в качестве ключа которого используется вершина, 
			в качестве значения список полигонов. 
			Конструктор удаляет из контейнера те записи которые соответствуют геометрии данного объекта. */
	MeshObstacle( std::map< Vector3D*, std::shared_ptr<std::set<std::shared_ptr<Poly>>> > &vecToTri );
	//! Конструктор класса, принимающий параметры: контейнер map< Vector3D*, shared_ptr<set<shared_ptr<Poly>>> >, уровень воды, является ли препятствием
	/*! Конструктор класса, принимающий параметры: контейнер, в качестве ключа которого используется вершина, 
			в качестве значения список полигонов, уровень воды. 
			Конструктор удаляет из контейнера те записи которые соответствуют геометрии данного объекта. */
	MeshObstacle( std::map< Vector3D*, std::shared_ptr<std::set<std::shared_ptr<Poly>>> > &vecToTri, const float &level, bool &isObstacle );
	//! Хранилище полигонов объекта
	std::set< std::shared_ptr<Poly> > tris;
	//! Найти ближайшее к точке P0 пересечение луча с полигоном
	/*! Пересечение исключает ребра полигонов.
			Вход: P0 - первая точка Vector3D луча
						P1 - вторая точка Vector3D луча
			Выход:	dst - точка перечечения
							face - грань пересечения
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool HalfIntersectRay( Vector3D &dst, std::shared_ptr<Poly> &face, const Vector3D &P0, const Vector3D &P1 );  // Проверка на пересечение прямой без ребер треугольника
	//! Найти любое пересечение луча с полигоном.
	/*! Пересечение исключает ребра полигонов. Обнаруживает только факт пересечения без нахождения полигонов и точек пересечения.
			Вход: P0 - первая точка Vector3D луча
						P1 - вторая точка Vector3D луча
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool HalfIntersectRay( const Vector3D &P0, const Vector3D &P1 );
	//! Найти ближайшее к точке P0 пересечение луча с полигоном
	/*! Пересечение засчитывается, если луч прошел полигон объекта а также если попал на ребро полигона.
			Вход: P0 - первая точка Vector3D луча
						P1 - вторая точка Vector3D луча
			Выход:	dst - точка перечечения
							face - грань пересечения
	*		@return	 Возвращает true если было перечение, иначе false	*/
	bool FullIntersectRay( Vector3D &dst, std::shared_ptr<Poly> &face, const Vector3D &P0, const Vector3D &P1 );	 // Проверка на пересечение прямой с реберами треугольника
	//! Найти любое пересечение луча с полигоном.
	/*! Пересечение засчитывается, если луч прошел полигон объекта а также если попал на ребро полигона.
			Обнаруживает только факт пересечения без возврата самих пересекаемых полигонов и точек пересечения.
	Вход: P0 - первая точка Vector3D луча
				P1 - вторая точка Vector3D луча
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool FullIntersectRay( const Vector3D &P0, const Vector3D &P1 );
	//! Найти ближайшее к точке P0 пересечение отрезка с полигоном
	/*! Пересечение исключает ребра полигонов.
			Вход: P0 - первая точка Vector3D луча
						P1 - вторая точка Vector3D луча
			Выход:	dst - точка перечечения
							face - грань пересечения
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool HalfIntersect( Vector3D &dst, std::shared_ptr<Poly> &face, const Vector3D &P0, const Vector3D &P1 );	// Проверка на пересечение отрезка без ребер треугольника
	//! Найти любое пересечение отрезка с полигоном.
	/*! Пересечение исключает ребра полигонов. Обнаруживает только факт пересечения без нахождения полигонов и точек пересечения.
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool HalfIntersect( const Vector3D &P0, const Vector3D &P1 );
	//! Найти ближайшее к точке P0 пересечение отрезка с полигоном
	/*! Пересечение засчитывается, если отрезок прошел полигон объекта а также если попал на ребро полигона.
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
			Выход:	dst - точка перечечения
							face - грань пересечения
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool FullIntersect( Vector3D &dst, std::shared_ptr<Poly> &face, const Vector3D &P0, const Vector3D &P1 );	// Проверка на пересечение отрезка с реберами треугольника
	//! Найти любое пересечение отрезка с полигоном.
	/*! Пересечение засчитывается, если отрезок прошел полигон объекта а также если попал на ребро полигона.
			Обнаруживает только факт пересечения без нахождения пересекаемых полигонов и точек пересечения.
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool FullIntersect( const Vector3D &P0, const Vector3D &P1 );
	//! Найти ближайшее к точке P0 пересечение отрезка с полигоном
	/*! Пересечение исключает ребра полигонов и начало отрезка P0, т.е. если точка P0 лежит в полигоне, пересечение не засчитывается.
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
			Выход:	dst - точка перечечения
							face - грань пересечения
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool HalfIntersectExcludingP0( Vector3D &dst, std::shared_ptr<Poly> &face, const Vector3D &P0, const Vector3D &P1 ); // Проверка на пересечение отрезка без ребер треугольника исключая начальную точку отрезка
	//! Найти любое пересечение отрезка с полигоном
	/*! Пересечение исключает ребра полигонов и начало отрезка P0, т.е. если точка P0 лежит в полигоне, пересечение не засчитывается.
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool HalfIntersectExcludingP0( const Vector3D &P0, const Vector3D &P1 );
	//! Найти ближайшее к точке P0 пересечение отрезка с полигоном
	/*! Пересечение засчитывается, если отрезок прошел полигон объекта, а также если попал на ребро полигона.
			Пересечение исключает начало отрезка P0, т.е. если точка P0 лежит в полигоне, пересечение не засчитывается.
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
			Выход:	dst - точка перечечения
							face - грань пересечения
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool FullIntersectExcludingP0( Vector3D &dst, std::shared_ptr<Poly> &face, const Vector3D &P0, const Vector3D &P1 ); // Проверка на пересечение отрезка с реберами треугольника исключая начальную точку отрезка
	//! Найти любое пересечение отрезка с полигоном
	/*! Пересечение засчитывается, если отрезок прошел полигон объекта, а также если попал на ребро полигона.
			Пересечение исключает начало отрезка P0, т.е. если точка P0 лежит в полигоне, пересечение не засчитывается.
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool FullIntersectExcludingP0( const Vector3D &P0, const Vector3D &P1 );
	//! Найти любое пересечение отрезка с полигоном
	/*! Пересечение засчитывается, если отрезок прошел полигон объекта, а также если попал на ребро полигона.
			Пересечение исключает начало отрезка P0, и конец P1.
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool FullIntersectExcludingBoth( const Vector3D &P0, const Vector3D &P1 );
	//! Найти ближайшее к точке P0 пересечение отрезка с полигоном
	/*! Пересечение засчитывается, если отрезок прошел полигон объекта, а также если попал на ребро полигона.
			Пересечение исключает начало отрезка P0, и конец P1.
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
			Выход:	dst - точка перечечения
							face - грань пересечения
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool FullIntersectExcludingBoth( Vector3D &dst, std::shared_ptr<Poly> &face, const Vector3D &P0, const Vector3D &P1 );
	//! Найти любое пересечение отрезка с объектом
	/*! Пересечение засчитывается, если отрезок прошел полигон объекта, а также если попал на ребро полигона.
			Пересечение исключает начало отрезка P0, т.е. если точка P0 лежит в полигоне.
			Если лишь P1 лежит на полигоне и отрезок ложится изнутри объекта то пересечение засчитывается
			Вход: P0 - первая точка Vector3D отрезка
						P1 - вторая точка Vector3D отрезка
	*		@return	 Возвращает true если было пересечение, иначе false	*/
	bool SuperIntersect( const Vector3D &P0, const Vector3D &P1 );
	//! Контейнер определящий связность между полигонами и ребрами
	std::map<Edge, std::shared_ptr<std::set<std::shared_ptr<Poly>>>> edgeToTri;
private:
	float level;
	//! Функция заполняет контейнер edgeToTri
	/*! Функция заполняет контейнер edgeToTri, причем ребра вставляются только те, 
			которые пересекаются с плоскостью y = level. */ 
	void FindEdges();
	//! Функция привязывает к полигонам их ребра
	void setUpEdges();
};

#endif
