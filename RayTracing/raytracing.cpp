#include "raytracing.h"

extern void calculateIntersection(std::vector<vector3f> &points,
								  std::vector<float> &lengths);

RayTracing::RayTracing()
{
}

void RayTracing::calculate(const std::vector<TriangleData> &td,
						   const std::vector<vector3f> &dir,
						   const vector3f &orig,
						   std::vector<vector3f> &points,
						   std::vector<float> &lengths,
						   const unsigned int gridSizeX,
						   const unsigned int gridSizeY)
{
	for (size_t i = 0; i < dir.size(); i++)
		rayIntersection.calculateIntersection(td, dir.at(i), orig, points, lengths);
}

void RayTracing::calculate(std::vector<vector3f> &points,
						   std::vector<float> &lengths)
{
	calculateIntersection(points, lengths);
}
