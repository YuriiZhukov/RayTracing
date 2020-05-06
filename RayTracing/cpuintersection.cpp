#include "cpuintersection.h"
#include <QDebug>

CPUIntersection::CPUIntersection(){}
CPUIntersection::~CPUIntersection(){}

float CPUIntersection::dot_product(float *a, float *b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

void CPUIntersection::cross_product(float *a, float *b, float *dest)
{
	dest[0] = a[1] * b[2] - a[2] * b[1];
	dest[1] = a[2] * b[0] - a[0] * b[2];
	dest[2] = a[0] * b[1] - a[1] * b[0];
}

void CPUIntersection::calculateIntersection(std::vector<vector3f> &points,
											std::vector<float> &lengths)
{
	IntersectionWizard& iw = IntersectionWizard::getInstance();
	if (!iw.dataCorrect())
	{
		qDebug() << "Data incorrect";
		return;
	}

	lengths.resize(iw.dirData().count);
	points.resize(iw.dirData().count);

	for (unsigned int i = 0; i < iw.dirData().count; i++)
	{
		float outPointsData[3];
		float outLengthsData;

		calculate(iw.objData().data, &iw.dirData().data[i*3], 
				  iw.origData().data, outPointsData,
				  &outLengthsData, iw.objData().size);

		vector3f point(outPointsData[0], outPointsData[1], outPointsData[2]);
		points[i] = point;
		lengths[i] = outLengthsData;
	}
}

void CPUIntersection::calculate(float *objData, float *dirData, float *origData, float *outPointsData, float *outLengthsData,
	unsigned int objDataSize)
{
	/*данные в dirData:
	0 = float x, 1 = float y, 2 = float z
	3 = float x, 4 = float y, 5 = float z и т.д до (dirDataSize / sizeof(float)) */

	float dir[3];
	dir[0] = dirData[0];
	dir[1] = dirData[1];
	dir[2] = dirData[2];

	float orig[3];
	orig[0] = origData[0];
	orig[1] = origData[1];
	orig[2] = origData[2];

	outPointsData[0] = 0;
	outPointsData[1] = 0;
	outPointsData[2] = 0;

	float minLength = 10000.0;
	*outLengthsData = minLength;

	/*Данные в objData:
	0, 1, 2 - нормаль 1й точки, 3, 4, 5 - координаты 1й точки
	6, 7, 8 - нормаль 2й точки, 9, 10, 11 - координаты 2й точки
	12, 13, 14 - нормаль 3й точки, 15, 16, 17 - координаты 3й точки
	и т.д до (objDataSize / sizeof(float)) */
	for (int i = 0; i < objDataSize; i += 18) //18 - размер одного TriangleData
	{
		float epsilon = 0.000001;
		float N[3], v0[3], v1[3], v2[3];

		N[0] = objData[i + 0];
		N[1] = objData[i + 1];
		N[2] = objData[i + 2];

		v0[0] = objData[i + 3];  v1[0] = objData[i + 9];   v2[0] = objData[i + 15];
		v0[1] = objData[i + 4];  v1[1] = objData[i + 10];  v2[1] = objData[i + 16];
		v0[2] = objData[i + 5];  v1[2] = objData[i + 11];  v2[2] = objData[i + 17];

		float denominator = dot_product(dir, N);
		if ((denominator >= 0.0 && denominator < epsilon) ||
			(denominator <  0.0 && denominator > -epsilon))
			continue;

		float v0minOrig[3];
		v0minOrig[0] = v0[0] - orig[0];
		v0minOrig[1] = v0[1] - orig[1];
		v0minOrig[2] = v0[2] - orig[2];
		float t = dot_product(v0minOrig, N) / denominator;
		if (t < 0)
			continue;

		float P[3];
		P[0] = orig[0] + dir[0] * t;
		P[1] = orig[1] + dir[1] * t;
		P[2] = orig[2] + dir[2] * t;

		float C0[3], C1[3], C2[3];
		float V1minV0[3], V2minV1[3], V0minV2[3];
		float PminV0[3], PminV1[3], PminV2[3];

		V1minV0[0] = v1[0] - v0[0];	 V2minV1[0] = v2[0] - v1[0];  V0minV2[0] = v0[0] - v2[0];
		V1minV0[1] = v1[1] - v0[1];	 V2minV1[1] = v2[1] - v1[1];  V0minV2[1] = v0[1] - v2[1];
		V1minV0[2] = v1[2] - v0[2];	 V2minV1[2] = v2[2] - v1[2];  V0minV2[2] = v0[2] - v2[2];

		PminV0[0] = P[0] - v0[0];  PminV1[0] = P[0] - v1[0];  PminV2[0] = P[0] - v2[0];
		PminV0[1] = P[1] - v0[1];  PminV1[1] = P[1] - v1[1];  PminV2[1] = P[1] - v2[1];
		PminV0[2] = P[2] - v0[2];  PminV1[2] = P[2] - v1[2];  PminV2[2] = P[2] - v2[2];

		cross_product(V1minV0, PminV0, C0);
		cross_product(V2minV1, PminV1, C1);
		cross_product(V0minV2, PminV2, C2);

		if (dot_product(N, C0) < 0.0 ||
			dot_product(N, C1) < 0.0 ||
			dot_product(N, C2) < 0.0)
			continue;

		if (t < minLength)
		{
			minLength = t;
			*outLengthsData = minLength;
			outPointsData[0] = P[0];
			outPointsData[1] = P[1];
			outPointsData[2] = P[2];
		}
	}
}