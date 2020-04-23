#include "intersectionwizard.h"


IntersectionWizard::IntersectionWizard() {}
IntersectionWizard::~IntersectionWizard() {}

IntersectionWizard& IntersectionWizard::getInstance()
{
	static IntersectionWizard instance;
	return instance;
}

void IntersectionWizard::setObjData(const std::vector<TriangleData> &td)
{
	_objData.data = (float*)&td[0];
	_objData.size = td.size() * sizeof(TriangleData) / sizeof(float);
	_objData.bytes = td.size() * sizeof(TriangleData);
}

void IntersectionWizard::setDirData(const std::vector<vector3f> &dir)
{
	_dirData.data = (float*)&dir[0];
	_dirData.size = dir.size() * sizeof(vector3f) / sizeof(float);
	_dirData.bytes = dir.size() * sizeof(vector3f);
}

void IntersectionWizard::setOrigData(const vector3f &orig)
{
	_origData.data = (float*)&orig;
	_origData.size = sizeof(vector3f) / sizeof(float);
	_origData.bytes = sizeof(vector3f);
}

CUData& IntersectionWizard::objData() {return _objData;};
CUData& IntersectionWizard::dirData() {return _dirData;};
CUData& IntersectionWizard::origData() {return _origData;};