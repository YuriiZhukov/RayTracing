#include "raytracing.h"

extern void calculateIntersection(std::vector<vector3f> &points,
								  std::vector<float> &lengths);

RayTracing::RayTracing()
{
}

void RayTracing::calculate_cpu(std::vector<vector3f> &points,
						   std::vector<float> &lengths)
{
	rayIntersection.calculateIntersection(points, lengths);
}

void RayTracing::calculate(std::vector<vector3f> &points,
						   std::vector<float> &lengths)
{
	calculateIntersection(points, lengths);
}

void RayTracing::setRaysGrid(float yawAngle, float pitchAngle, int raysByYaw, int raysByPitch)
{
	ray.setGridParams(yawAngle, pitchAngle, raysByYaw, raysByPitch);
}

void RayTracing::setRayPosition(float x, float y, float z)
{
	ray.setPosition(x, y, z);
}

void RayTracing::setRayRotation(float yaw, float pitch, float roll)
{
	ray.setRotation(yaw, pitch, roll);
}

bool RayTracing::load(std::string & filepath)
{
	return objLoader.load(filepath);
}

