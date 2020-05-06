#pragma once
#include <vector>
#include "structs.h"
#include "intersectionwizard.h"

class CPUIntersection
{
public:
	CPUIntersection();
	virtual ~CPUIntersection();

	void calculateIntersection(std::vector<vector3f> &points,
							   std::vector<float> &lengths);

private:
	void calculate(float *objData, float *dirData, float *origData, float *outPointsData, float *outLengthsData,
		unsigned int objDataSize);
	float dot_product(float *a, float *b);
	void cross_product(float *a, float *b, float *dest);

};

