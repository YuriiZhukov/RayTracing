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
	/*Установить позицию камеры*/
	void setPosition(float x, float y, float z);
	/*Установить поворот камеры !! В РАДИАНАХ !! */
	void setRotation(float yaw, float pitch, float roll);
	/*Получить вектор поворота камеры*/
	const Matrix3x3& rotationMatrix() const;
	/*Получить вектор позиции луча*/
	const vector3f& rotation() const;
	/*Получить вектор позиции луча*/
	const vector3f& position() const;
	/*Получить вектор направления луча*/
	const vector3f& direction() const;
	/*Получить вектора направлений лучей*/
	const std::vector<vector3f>& directions() const;
	/*Установить параметры сетки*/
	void Ray::setGridParams(float yawAngle, float pitchAngle,
							int raysByYaw, int raysByPitch);

private:
	/*Установить вектор направленности камеры*/ //убрать или оставить
	void setDirection(float x, float y, float z);
	/*Расчет лучей в соответствии с сеткой*/
	void setRaysGrid();

private:
	/*вектор поворота центрального луча*/
	vector3f _rotation;
	/*координаты начала лучей*/
	vector3f _position;
	/*вектор направления центрального луча*/
	vector3f _direction;
	/*Кватернион для поворота камеры*/
	QQuaternion quaternion;
	/*Вектора направлений лучей*/
	std::vector<vector3f> _directions;
	/*Результирующая матрица поворота */
	Matrix3x3 _matrix;
};

