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
	_objData.count = td.size();
	_objData.data = (float*)&td[0];
	_objData.bytes = td.size() * sizeof(TriangleData);
	_objData.size = _objData.bytes / sizeof(float);
}

void IntersectionWizard::setDirData(const std::vector<vector3f> &dir)
{
	_dirData.count = dir.size();
	_dirData.data = (float*)&dir[0];
	_dirData.bytes = dir.size() * sizeof(vector3f);
	_dirData.size = _dirData.bytes / sizeof(float);
}

void IntersectionWizard::setOrigData(const vector3f &orig)
{
	_origData.count = 1;
	_origData.data = (float*)&orig;
	_origData.bytes = sizeof(vector3f);
	_origData.size = _origData.bytes / sizeof(float);
}

void IntersectionWizard::setGridData(float yawAngle, float pitchAngle,
									 int raysByYaw, int raysByPitch)
{
	if (raysByYaw <= 0 || raysByPitch <= 0)
	{
		raysByYaw = 1;
		raysByPitch = 1;
	}

	float delta = 0.000001;
	if (yawAngle <= delta || pitchAngle <= delta)
	{
		yawAngle = 0.1;
		pitchAngle = 0.1;
	}

	_gridData.yawAngle = yawAngle;
	_gridData.pitchAngle = pitchAngle;
	_gridData.raysByYaw = raysByYaw;
	_gridData.raysByPitch = raysByPitch;
}

CUData& IntersectionWizard::objData() {return _objData;};
CUData& IntersectionWizard::dirData() {return _dirData;};
CUData& IntersectionWizard::origData() { return _origData; }; 
GridData& IntersectionWizard::gridData() { return _gridData; };