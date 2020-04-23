#include <qelapsedtimer.h>
#include "ray.h"

Ray::Ray() : _direction(1.0, 0.0, 0.0) {}
Ray::~Ray() {}

void Ray::setPosition(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

void Ray::setDirection(float x, float y, float z)
{
	_directions.clear();

	_direction.x = x;
	_direction.y = y;
	_direction.z = z;

	quaternion = QQuaternion::fromDirection(QVector3D(_direction.x, _direction.y, _direction.z), QVector3D(0, 1, 0));

	_rotation.x = quaternion.vector().x();
	_rotation.y = quaternion.vector().y();
	_rotation.z = quaternion.vector().z();
}

void Ray::setRotation(float yaw, float pitch, float roll)
{
	_directions.clear();

#ifdef USE_QUATERNIONS
	/*Порядок произведения кватернионов аналогичен
	порядку произведений матриц по Эйлеру
	(оси поменены местами ( в qt x-->z ????? ))
	1 - yaw		вокруг оси Y (вверх) 
	2 - pitch	вокруг оси X (вперед)
	3 - roll	вокруг оси Z (вправо) */
	quaternion = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), deg2rad(yaw)) *
				 QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), deg2rad(pitch)) *
				 QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), deg2rad(roll));

	//float yaw, pitch, roll;
	//quaternion.getEulerAngles(&pitch, &yaw, &roll);

	_rotation.x = yaw;
	_rotation.y = pitch;
	_rotation.z = roll;

	QVector3D d = quaternion.rotatedVector(QVector3D(0.0, 0.0, 1.0));

	_direction.x = d.x();
	_direction.y = d.y();
	_direction.z = d.z();
	_direction.normalize();

#else
	_matrix.setRotation(yaw, pitch, roll);
	_rotation = _matrix.rotation();
	_direction = _matrix.direction();
#endif

	setRaysGrid();
}

void Ray::setRaysGrid()
{
	IntersectionWizard& iw = IntersectionWizard::getInstance();

	float betaStep = iw.gridData().yawAngle / float(iw.gridData().raysByYaw); /*<---->*/
	
	float epsilonStep = iw.gridData().pitchAngle / float(iw.gridData().raysByPitch);

	for (int i = -iw.gridData().raysByPitch / 2; i <= iw.gridData().raysByPitch / 2; i++)
	{
		if ((i == 0) && (iw.gridData().raysByPitch % 2 == 0))
			continue;
		for (int j = iw.gridData().raysByYaw / 2; j >= -iw.gridData().raysByYaw / 2; j--)
		{
			if ((j == 0) && (iw.gridData().raysByYaw % 2 == 0))
				continue;

#ifdef USE_QUATERNIONS
			QQuaternion quat =
				QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), rad2deg(_rotation.x + xStep * i)) *
				QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), rad2deg(_rotation.y + yStep * j)) *
				QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), rad2deg(_rotation.z));

			vector3f dir;

			QVector3D d = quat.rotatedVector(QVector3D(0.0, 0.0, 1.0));

			dir.x = d.x();
			dir.y = d.y();
			dir.z = d.z();
			dir.normalize();

			_directions.push_back(dir);
#else
			Matrix3x3 mat;
			mat.setRotation(_rotation.x + betaStep * j,
							_rotation.y + epsilonStep * i,
							_rotation.z);

			_directions.push_back(mat.direction());
#endif
		}
	}
}

const Matrix3x3 & Ray::rotationMatrix() const { return _matrix; }
const vector3f & Ray::rotation() const {return _rotation; }
const vector3f & Ray::position() const {return _position; }
const vector3f & Ray::direction() const { return _direction; }
const std::vector<vector3f> & Ray::directions() const { return _directions; }