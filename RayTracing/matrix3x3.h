#pragma once

#include <math.h>
#include "structs.h"

struct Matrix3x3
{
	explicit Matrix3x3(int a = 0.0) : m00(a), m01(a), m02(a),
									  m10(a), m11(a), m12(a), 
									  m20(a), m21(a), m22(a) {};

	/*���������� ������ �������������� �� ���� x, y, z */
	vector3f direction();
	/*���������� ���� ��������: yaw (OY), pitch (OZ), roll (OX) */
	vector3f rotation();
	/*������ ������� ������� ���������������� ������������� 
	������ �� ������� ����: yaw (OY), pitch (OZ), roll (OX) */
	void setRotation(float yaw, float pitch, float roll);
	/*���������� ������� �������� ����������������� ������������
	������ �� ������� ����: yaw (OY), pitch (OZ), roll (OX) 
	!! � �������� !! */
	static Matrix3x3 fromRotation(float yaw, float pitch, float roll);

private:
	float m00, m01, m02,
		  m10, m11, m12,
		  m20, m21, m22;

	vector3f _rotation;
	vector3f _direction;
};
