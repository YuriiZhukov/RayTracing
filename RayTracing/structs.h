#pragma once

#include "vector3f.h"
#include "matrix3x3.h"
#include <math.h>
#include <vector>

/*Формат записи поверхностей "f ..." */
enum FaceType
{
	unknown = 0,	//  Не определен
	vt,				// "Вершины / Текстурные координаты"
	vtn,			// "Вершины / Текстурные координаты / Нормали"
	vn				// "Вершины // Нормали"
};


struct TrianglePoint
{
	vector3f normals;
	vector3f coords;
};

struct TriangleData
{
	explicit TriangleData() {}
	explicit TriangleData(TrianglePoint p0, TrianglePoint p1, TrianglePoint p2) :
														p0(p0), p1(p1), p2(p2) {};
	TrianglePoint p0;
	TrianglePoint p1;
	TrianglePoint p2;
};

static float rad2deg(float rad)
{
	return rad * 180.0 / M_PI;
}

static float deg2rad(float deg)
{
	return deg / 180.0 * M_PI;
}

static float dot_product(const vector3f& a, const vector3f& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

static vector3f cross_product(const vector3f& a, const vector3f& b)
{
	return vector3f(a.y * b.z - a.z * b.y,
					a.z * b.x - a.x * b.z,
					a.x * b.y - a.y * b.x);
}

