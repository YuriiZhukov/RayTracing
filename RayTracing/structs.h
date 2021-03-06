#pragma once

#include "vector3f.h"
#include "matrix3x3.h"
#include <math.h>
#include <vector>

/*������ ������ ������������ "f ..." */
enum FaceType
{
	unknown = 0,	//  �� ���������
	vt,				// "������� / ���������� ����������"
	vtn,			// "������� / ���������� ���������� / �������"
	vn				// "������� // �������"
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
