#include <QDebug>
#include "matrix3x3.h"

void Matrix3x3::setRotation(float yaw, float pitch, float roll)
{
	this->yaw = yaw;
	this->pitch = pitch;
	this->roll = roll;

	/* c - cos, s - sin;
	p - psi(yaw, OY), t - theta(pitch, OY), g - gamma(roll, OY) */
	float cp, sp, ct, st, cg, sg;
	cp = cos(yaw);
	sp = sin(yaw);
	ct = cos(pitch);
	st = sin(pitch);
	cg = cos(roll);
	sg = sin(roll);

	/*Первый ряд*/
	m00 = ct * cg;
	m01 = -st;
	m02 = ct * sg;
	/*Второй ряд*/
	m10 = cp * st * cg + sp * sg;
	m11 = cp * ct;
	m12 = cp * st * sg - sp * cg;
	/*Третий ряд*/
	m20 = sp * st * cg - cp * sg;
	m21 = sp * ct;
	m22 = sp * st * sg - cp * cg;

	this->_rotation = vector3f(yaw, pitch, roll);
	this->_direction = vector3f(m21, m01, m11);

	/*
	qDebug() << "|" << m00 << " ; " << m01 << " ; " << m02 << "|" << "\n"
			 << "|" << m10 << " ; " << m11 << " ; " << m12 << "|" << "\n"
			 << "|" << m20 << " ; " << m21 << " ; " << m22 << "|" << "\n";
	*/ 
}

Matrix3x3 Matrix3x3::fromRotation(float yaw, float pitch, float roll)
{
	Matrix3x3 mat(0);
	mat.setRotation(yaw, pitch, roll);
	return Matrix3x3();
}

vector3f Matrix3x3::direction() { return _direction; }
vector3f Matrix3x3::rotation() { return _rotation; }
