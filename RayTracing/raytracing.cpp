#include "raytracing.h"

extern void calculateIntersection(const std::vector<TriangleData> &td,
								  const std::vector<vector3f> &dir,
								  const vector3f &orig,
								  std::vector<vector3f> &points,
								  std::vector<float> &lengths,
								  const unsigned int gridSizeX,
								  const unsigned int gridSizeY);

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
#ifdef CUDA_CALC
	/*Запуск CUDA*/
	calculateIntersection(td, dir, orig, points, lengths, gridSizeX, gridSizeY);
#else
	for (size_t i = 0; i < dir.size(); i++)
		rayIntersection.calculateIntersection(td, dir.at(i), orig, points, lengths);
#endif
}
