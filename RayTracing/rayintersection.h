#pragma once
#include <vector>
#include "structs.h"

class RayIntersection
{
public:
	RayIntersection();
	virtual ~RayIntersection();

	void calculateIntersection(const std::vector<TriangleData> &td,
							   const vector3f &dir,
							   const vector3f &orig,
							   std::vector<vector3f> &points,
							   std::vector<float> &lengths);
};

