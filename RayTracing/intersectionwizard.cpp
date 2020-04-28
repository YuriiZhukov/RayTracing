#include "intersectionwizard.h"


IntersectionWizard::IntersectionWizard() : objCorrect(false), dirCorrect(false),
										   origCorrect(false), gridCorrect(false) {}
IntersectionWizard::~IntersectionWizard() {}

IntersectionWizard& IntersectionWizard::getInstance()
{
	static IntersectionWizard instance;
	return instance;
}

void IntersectionWizard::setObjData(const std::vector<TriangleData> &td)
{
	if (td.size() > 0)
		objCorrect = true;
	else
	{
		objCorrect = false;
		return;
	}
	_objData.count = td.size();
	_objData.data = (float*)&td[0];
	_objData.bytes = td.size() * sizeof(TriangleData);
	_objData.size = _objData.bytes / sizeof(float);
}

void IntersectionWizard::setDirData(const std::vector<vector3f> &dir)
{
	if (dir.size() > 0)
		dirCorrect = true;
	else
	{
		dirCorrect = false;
		return;
	}

	_dirData.count = dir.size();
	_dirData.data = (float*)&dir[0];
	_dirData.bytes = dir.size() * sizeof(vector3f);
	_dirData.size = _dirData.bytes / sizeof(float);
}

void IntersectionWizard::setOrigData(const vector3f &orig)
{
	origCorrect = true;

	_origData.count = 1;
	_origData.data = (float*)&orig;
	_origData.bytes = sizeof(vector3f);
	_origData.size = _origData.bytes / sizeof(float);
}

void IntersectionWizard::setGridData(float yawAngle, float pitchAngle,
									 int raysByYaw, int raysByPitch)
{
	float delta = 0.000001;
	if (yawAngle <= delta || pitchAngle <= delta || raysByPitch <= 0 || raysByYaw <= 0)
	{
		gridCorrect = false;
		return;
	}
	else gridCorrect = true;

	_gridData.yawAngle = yawAngle;
	_gridData.pitchAngle = pitchAngle;
	_gridData.raysByYaw = raysByYaw;
	_gridData.raysByPitch = raysByPitch;
}

bool IntersectionWizard::dataCorrect()
{
	return (objCorrect && dirCorrect && origCorrect && gridCorrect);
}

CUData& IntersectionWizard::objData() {return _objData; };
CUData& IntersectionWizard::dirData() {return _dirData; };
CUData& IntersectionWizard::origData() {return _origData; }; 
GridData& IntersectionWizard::gridData() {return _gridData; };