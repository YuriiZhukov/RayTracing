#include <qdebug.h>
#include <qelapsedtimer.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include "structs.h"
#include "intersectionwizard.h"

/*float *objData = nullptr;
float* dev_objData;
unsigned int objDataBytes = 0;
unsigned int objDataSize = 0;*/

bool temp = false;

static void HandleError(cudaError_t err,
	const char *file,
	int line) {
	if (err != cudaSuccess) {
		printf("%s in %s at line %d\n", cudaGetErrorString(err),
			file, line);
		exit(EXIT_FAILURE);
	}
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))

__device__ float dot_product(float *a, float *b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

__device__ void cross_product(float *a, float *b, float *dest)
{
	dest[0] = a[1] * b[2] - a[2] * b[1];
	dest[1] = a[2] * b[0] - a[0] * b[2];
	dest[2] = a[0] * b[1] - a[1] * b[0];
}

__global__ void calcIntersection(float *objData, float *dirData, float *origData, float *outPointsData, float *outLengthsData,
								 unsigned int objDataSize)
{
	int tid =  blockIdx.x * blockDim.x + threadIdx.x; //ID указывает на один луч (одно направление) из *dirData

	/*данные в dirData:
	0 = float x, 1 = float y, 2 = float z
	3 = float x, 4 = float y, 5 = float z и т.д до (dirDataSize / sizeof(float)) */

	float dir[3];
	dir[0] = dirData[tid * 3 + 0];
	dir[1] = dirData[tid * 3 + 1];
	dir[2] = dirData[tid * 3 + 2];

	float orig[3];
	orig[0] = origData[0];
	orig[1] = origData[1];
	orig[2] = origData[2];

	outPointsData[tid * 3 + 0] = 0;
	outPointsData[tid * 3 + 1] = 0;
	outPointsData[tid * 3 + 2] = 0;

	float minLength = 50.0;
	outLengthsData[tid] = minLength;

	/*Данные в objData:
	0, 1, 2 - нормаль 1й точки, 3, 4, 5 - координаты 1й точки
	6, 7, 8 - нормаль 2й точки, 9, 10, 11 - координаты 2й точки
	12, 13, 14 - нормаль 3й точки, 15, 16, 17 - координаты 3й точки
	и т.д до (objDataSize / sizeof(float)) */
	for (int i = 0; i < objDataSize; i+=18) //18 - размер одного TriangleData
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

		//float currentLength = distance(orig, P);
		if (t < minLength)
		{
			minLength = t;
			outLengthsData[tid] = minLength;
			outPointsData[tid * 3 + 0] = P[0];
			outPointsData[tid * 3 + 1] = P[1];
			outPointsData[tid * 3 + 2] = P[2];
		}
	}
}

#if 0
void calculateIntersection(const std::vector<TriangleData> &td,
						   const std::vector<vector3f> &dir,
						   const vector3f &orig,
						   std::vector<vector3f> &points,
						   std::vector<float> &lengths,
						   const unsigned int gridSizeBeta,
						   const unsigned int gridSizeEpsilon)
{
	QElapsedTimer tmr;
	tmr.start();

	IntersectionWizard& iw = IntersectionWizard::getInstance();

	/*данные сцены*/
	if (objData == nullptr)
	{
		objDataBytes = td.size() * sizeof(TriangleData);
		objDataSize = td.size() * sizeof(TriangleData) / sizeof(float);
		objData = (float*)&td[0];// new float[objDataSize];
		memcpy(objData, &td[0], objDataBytes);
		HANDLE_ERROR(cudaMalloc((void**)&dev_objData, objDataBytes));
		HANDLE_ERROR(cudaMemcpy(dev_objData, objData, objDataBytes, cudaMemcpyHostToDevice));
	}

	/*данные векторов направлений*/
	unsigned int dirDataBytes  = dir.size() * sizeof(vector3f);
	unsigned int dirDataSize = dir.size() * sizeof(vector3f) / sizeof(float);
	float *dirData = new float[dirDataSize];
	memcpy(dirData, &dir[0], dirDataBytes);
	float* dev_dirData;
	HANDLE_ERROR(cudaMalloc((void**)&dev_dirData, dirDataBytes));
	HANDLE_ERROR(cudaMemcpy(dev_dirData, dirData, dirDataBytes, cudaMemcpyHostToDevice));

	/*данные позиции*/
	unsigned int origDataBytes = sizeof(vector3f);
	unsigned int origDataSize = sizeof(vector3f) / sizeof(float);
	float *origData = new float[origDataSize];
	memcpy(origData, &orig, origDataBytes);
	float* dev_origData;
	HANDLE_ERROR(cudaMalloc((void**)&dev_origData, origDataBytes));
	HANDLE_ERROR(cudaMemcpy(dev_origData, origData, origDataBytes, cudaMemcpyHostToDevice));

	/*выходные данные точек пересечения*/
	unsigned int outPointsDataBytes = dir.size() * sizeof(vector3f);
	unsigned int outPointsDataSize = dir.size() * sizeof(vector3f) / sizeof(float);
	float *outPointsData  = new float[outPointsDataSize];
	float* dev_outPointsData;
	HANDLE_ERROR(cudaMallocHost((void**)&dev_outPointsData, outPointsDataBytes));

	/*выходные данные дальностей до точек пересечения*/
	unsigned int outLengthsDataBytes = dir.size() * sizeof(float);
	unsigned int outLengthsDataSize = dir.size();
	float *outLengthsData = new float[outLengthsDataSize];
	float* dev_outLengthsData;
	HANDLE_ERROR(cudaMallocHost((void**)&dev_outLengthsData, outLengthsDataBytes));

	dim3 grid(gridSizeBeta * gridSizeEpsilon, 1);
	calcIntersection<<<gridSizeBeta, gridSizeEpsilon >>>(dev_objData, dev_dirData, 
														 dev_origData, dev_outPointsData,
														 dev_outLengthsData, objDataSize);

	HANDLE_ERROR(cudaMemcpy(outPointsData, dev_outPointsData, outPointsDataBytes, cudaMemcpyDeviceToHost));
	HANDLE_ERROR(cudaMemcpy(outLengthsData, dev_outLengthsData, outLengthsDataBytes, cudaMemcpyDeviceToHost));
	
	for (unsigned int i = 0; i < dir.size(); i++)
	{
		vector3f point(outPointsData[i * 3 + 0], outPointsData[i * 3 + 1], outPointsData[i * 3 + 2]);
		points.push_back(point);
		lengths.push_back(outLengthsData[i]);
	}

	cudaFree(dev_dirData);
	cudaFree(dev_origData);
	cudaFreeHost(dev_outPointsData);
	cudaFreeHost(dev_outLengthsData);

	delete[] dirData;
	delete[] origData;
	delete[] outPointsData;
	delete[] outLengthsData;

	quint64 time = tmr.elapsed();
	qDebug() << "Time = " << time;
}
#else
void calculateIntersection(const std::vector<TriangleData> &td,
	const std::vector<vector3f> &dir,
	const vector3f &orig,
	std::vector<vector3f> &points,
	std::vector<float> &lengths,
	const unsigned int gridSizeBeta,
	const unsigned int gridSizeEpsilon)
{
	QElapsedTimer tmr;
	tmr.start();

	IntersectionWizard& iw = IntersectionWizard::getInstance();

	/*данные сцены*/
	float* dev_objData;
	HANDLE_ERROR(cudaMalloc((void**)&dev_objData, iw.objData().bytes));
	HANDLE_ERROR(cudaMemcpy(dev_objData, iw.objData().data, iw.objData().bytes, cudaMemcpyHostToDevice));

	/*данные векторов направлений*/
	float* dev_dirData;
	HANDLE_ERROR(cudaMalloc((void**)&dev_dirData, iw.dirData().bytes));
	HANDLE_ERROR(cudaMemcpy(dev_dirData, iw.dirData().data, iw.dirData().bytes, cudaMemcpyHostToDevice));

	/*данные позиции*/
	float* dev_origData;
	HANDLE_ERROR(cudaMalloc((void**)&dev_origData, iw.origData().bytes));
	HANDLE_ERROR(cudaMemcpy(dev_origData, iw.origData().data, iw.origData().bytes, cudaMemcpyHostToDevice));

	/*выходные данные точек пересечения*/
	unsigned int outPointsDataBytes = dir.size() * sizeof(vector3f);
	unsigned int outPointsDataSize = dir.size() * sizeof(vector3f) / sizeof(float);
	float *outPointsData = new float[outPointsDataSize];
	float* dev_outPointsData;
	HANDLE_ERROR(cudaMallocHost((void**)&dev_outPointsData, outPointsDataBytes));

	/*выходные данные дальностей до точек пересечения*/
	unsigned int outLengthsDataBytes = dir.size() * sizeof(float);
	unsigned int outLengthsDataSize = dir.size();
	float *outLengthsData = new float[outLengthsDataSize];
	float* dev_outLengthsData;
	HANDLE_ERROR(cudaMallocHost((void**)&dev_outLengthsData, outLengthsDataBytes));

	dim3 grid(gridSizeBeta * gridSizeEpsilon, 1);
	calcIntersection << <gridSizeBeta, gridSizeEpsilon >> > (dev_objData, dev_dirData,
		dev_origData, dev_outPointsData,
		dev_outLengthsData, iw.objData().size);

	HANDLE_ERROR(cudaMemcpy(outPointsData, dev_outPointsData, outPointsDataBytes, cudaMemcpyDeviceToHost));
	HANDLE_ERROR(cudaMemcpy(outLengthsData, dev_outLengthsData, outLengthsDataBytes, cudaMemcpyDeviceToHost));

	for (unsigned int i = 0; i < dir.size(); i++)
	{
		vector3f point(outPointsData[i * 3 + 0], outPointsData[i * 3 + 1], outPointsData[i * 3 + 2]);
		points.push_back(point);
		lengths.push_back(outLengthsData[i]);
	}

	cudaFree(dev_objData);
	cudaFree(dev_dirData);
	cudaFree(dev_origData);
	cudaFreeHost(dev_outPointsData);
	cudaFreeHost(dev_outLengthsData);

	delete[] outPointsData;
	delete[] outLengthsData;

	quint64 time = tmr.elapsed();
	qDebug() << "Time = " << time;
}

#endif
