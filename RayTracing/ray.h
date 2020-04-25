#pragma once

///#define USE_QUATERNIONS

#include <qquaternion.h>
#include "structs.h"
#include "intersectionwizard.h"

class Ray
{
public:
	Ray();
	virtual ~Ray();

public:
	/*���������� ������� ������*/
	void setPosition(float x, float y, float z);
	/*���������� ������� ������ !! � �������� !! */
	void setRotation(float yaw, float pitch, float roll);
	/*�������� ������ �������� ������*/
	const Matrix3x3& rotationMatrix() const;
	/*�������� ������ ������� ����*/
	const vector3f& rotation() const;
	/*�������� ������ ������� ����*/
	const vector3f& position() const;
	/*�������� ������ ����������� ����*/
	const vector3f& direction() const;
	/*�������� ������� ����������� �����*/
	const std::vector<vector3f>& directions() const;
	/*���������� ��������� �����*/
	void Ray::setGridParams(float yawAngle, float pitchAngle,
							int raysByYaw, int raysByPitch);

private:
	/*���������� ������ �������������� ������*/ //������ ��� ��������
	void setDirection(float x, float y, float z);
	/*������ ����� � ������������ � ������*/
	void setRaysGrid();

private:
	/*������ �������� ������������ ����*/
	vector3f _rotation;
	/*���������� ������ �����*/
	vector3f _position;
	/*������ ����������� ������������ ����*/
	vector3f _direction;
	/*���������� ��� �������� ������*/
	QQuaternion quaternion;
	/*������� ����������� �����*/
	std::vector<vector3f> _directions;
	/*�������������� ������� �������� */
	Matrix3x3 _matrix;
};

