#pragma once
#include "structs.h"
#include "rayintersection.h"
#include "intersectionwizard.h"

#define CUDA_CALC

class RayTracing
{
public:
	RayTracing();
	void calculate(const std::vector<TriangleData> &td,
				   const std::vector<vector3f> &dir,
				   const vector3f &orig,
				   std::vector<vector3f> &points,
				   std::vector<float> &lengths,
				   const unsigned int gridSizeBeta,
				   const unsigned int gridSizeEpsilon);
private:
	RayIntersection rayIntersection;

};