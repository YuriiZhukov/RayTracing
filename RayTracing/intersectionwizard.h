#pragma once

#include "structs.h"

struct CUData
{
	CUData() : data(nullptr), size(0), bytes(0), count(0) {}
	float* data;
	unsigned int count;
	unsigned int size;
	unsigned int bytes;
};

struct GridData
{
	GridData() : yawAngle(0.0), pitchAngle(0.0), 
		raysByYaw(0), raysByPitch(0) {}
	float yawAngle;
	float pitchAngle;
	int raysByYaw;
	int raysByPitch;
};

class IntersectionWizard
{
private:
	IntersectionWizard();
	IntersectionWizard(const IntersectionWizard&) = delete;
	IntersectionWizard& operator=(const IntersectionWizard&) = delete;
	virtual ~IntersectionWizard();

public:
	static IntersectionWizard &getInstance();
	void setObjData(const std::vector<TriangleData> &td);
	void setDirData(const std::vector<vector3f> &dir);
	void setOrigData(const vector3f &orig);
	void setGridData(float yawAngle, float pitchAngle, 
					 int raysByYaw, int raysByPitch);

	CUData& objData();
	CUData& dirData();
	CUData& origData();
	GridData& gridData();

private:
	CUData _objData;
	CUData _dirData;
	CUData _origData;
	GridData _gridData;
};

