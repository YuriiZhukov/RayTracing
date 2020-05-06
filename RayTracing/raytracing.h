#pragma once
#include "structs.h"
#include "cpuintersection.h"
#include "intersectionwizard.h"
#include "ray.h"
#include "objloader.h"

class RayTracing
{
public:
	RayTracing();
	
	/*Расчет на CPU*/
	void calculate_cpu(std::vector<vector3f> &points,
					   std::vector<float> &lengths);
	/*Расчет на GPU*/
	void calculate(std::vector<vector3f> &points,
				   std::vector<float> &lengths);
	/**/
	void setRaysGrid(float yawAngle, float pitchAngle,
					 int raysByYaw, int raysByPitch);
	/**/
	void setRayPosition(float x, float y, float z);
	/**/
	void setRayRotation(float yaw, float pitch, float roll);
	/**/
	bool load(std::string& filepath);


private:
	CPUIntersection rayIntersection;
	Ray ray;
	ObjLoader objLoader;
};