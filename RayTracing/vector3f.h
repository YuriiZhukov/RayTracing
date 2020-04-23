#pragma once

#include <math.h>
#include "structs.h"

struct vector3f
{
	vector3f() : x(0.0), y(0.0), z(0.0) {}
	vector3f(float x, float y, float z) : x(x), y(y), z(z) {}

	float x;
	float y;
	float z;

	float distance(const vector3f& a) const
	{
		return sqrt(pow(a.x - x, 2) +
			pow(a.y - y, 2) +
			pow(a.z - z, 2));
	}
	float length()
	{
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}
	void normalize()
	{
		float len = length();
		x /= len;
		y /= len;
		z /= len;
	}

	vector3f operator*(float f) const
	{
		return vector3f(x*f, y*f, z*f);
	}
	friend vector3f operator*(float f, const vector3f& a)
	{
		return vector3f(a.x*f, a.y*f, a.z*f);
	}
	friend vector3f operator*(const vector3f& l, const vector3f& r)
	{
		return vector3f(l.x*r.x, l.y*r.y, l.z*r.z);
	}
	friend vector3f operator+(const vector3f& l, const vector3f& r)
	{
		return vector3f(l.x + r.x, l.y + r.y, l.z + r.z);
	}
	friend vector3f operator-(const vector3f& l, const vector3f& r)
	{
		return vector3f(l.x - r.x, l.y - r.y, l.z - r.z);
	}
};
