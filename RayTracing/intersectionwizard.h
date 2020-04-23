#pragma once

#include "structs.h"

struct CUData
{
	CUData() : data(nullptr), size(0), bytes(0) {}
	float* data;
	unsigned int size;
	unsigned int bytes;
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

	CUData& objData();
	CUData& dirData();
	CUData& origData();

private:
	CUData _objData;
	CUData _dirData;
	CUData _origData;
};

