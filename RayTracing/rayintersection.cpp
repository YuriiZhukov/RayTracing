#include "rayintersection.h"

RayIntersection::RayIntersection(){}
RayIntersection::~RayIntersection(){}

void RayIntersection::calculateIntersection(const std::vector<TriangleData> &td,
												const vector3f &dir,
												const vector3f &orig,
												std::vector<vector3f> &points,
												std::vector<float> &lengths)
{
	vector3f minP;
	float minLength = 1000000.0;

	for (size_t i = 0; i < td.size(); i++)
	{
		float epsilon = 0.000001;
		vector3f N = td[i].p0.normals;
		vector3f v0 = td[i].p0.coords;
		vector3f v1 = td[i].p1.coords;
		vector3f v2 = td[i].p2.coords;

		float denominator = dot_product(dir, N);
		if (fabs(denominator) < epsilon)
			continue;

		float t = dot_product((v0 - orig), N) / denominator;
		if (t < 0)
			continue;

		vector3f P = orig + dir * t;

		/*----------------------------------------------
		Описание используемых в дальнейшем векторов
		vector3f edge0 = v1 - v0;
		vector3f edge1 = v2 - v1;
		vector3f edge2 = v0 - v2;
		vector3f vp0 = P - v0;
		vector3f vp1 = P - v1;
		vector3f vp2 = P - v2;
		vector3f C0	= cross_product(edge0, vp0);
		vector3f C1	= cross_product(edge1, vp1);
		vector3f C2	= cross_product(edge2, vp2);
		-----------------------------------------------*/

		vector3f C0 = cross_product((v1 - v0), (P - v0));
		vector3f C1 = cross_product((v2 - v1), (P - v1));
		vector3f C2 = cross_product((v0 - v2), (P - v2));

		if (dot_product(N, C0) < 0 ||
			dot_product(N, C1) < 0 ||
			dot_product(N, C2) < 0)
			continue;

		if (t < minLength)
		{
			minLength = t;
			minP = P;
		}
	}

	points.push_back(minP);
	lengths.push_back(minLength);
}