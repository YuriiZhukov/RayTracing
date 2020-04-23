#pragma once
#include "structs.h"
#include "rayintersection.h"
#include "intersectionwizard.h"

class RayTracing
{
public:
	RayTracing();
	/*Расчет на CPU*/
	void calculate(const std::vector<TriangleData> &td,
				   const std::vector<vector3f> &dir,
				   const vector3f &orig,
				   std::vector<vector3f> &points,
				   std::vector<float> &lengths,
				   const unsigned int gridSizeBeta,
				   const unsigned int gridSizeEpsilon);
	
	/*Расчет на GPU*/
	void calculate(std::vector<vector3f> &points,
				   std::vector<float> &lengths);

private:
	RayIntersection rayIntersection;

};