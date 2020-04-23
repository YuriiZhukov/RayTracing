#include <qelapsedtimer.h>
#include "raygrid.h"

RayGrid::RayGrid() : _direction(1.0, 0.0, 0.0),
			 beta(0.0), epsilon(0.0), 
			 gridSizeBeta(0), gridSizeEpsilon(0) {}
RayGrid::~RayGrid() {}

void RayGrid::setPosition(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

void RayGrid::setDirection(float x, float y, float z)
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

void RayGrid::setRotation(float yaw, float pitch, float roll)
{
	_directions.clear();

#ifdef USE_QUATERNIONS
	/*������� ������������ ������������ ����������
	������� ������������ ������ �� ������
	(��� �������� ������� ( � qt x-->z ????? ))
	1 - yaw		������ ��� Y (�����) 
	2 - pitch	������ ��� X (������)
	3 - roll	������ ��� Z (������) */
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

void RayGrid::setGrid(float beta, float epsilon,
	int gridSizeBeta, int gridSizeEpsilon)
{
	this->beta = beta;
	this->epsilon = epsilon;
	this->gridSizeBeta = gridSizeBeta;
	this->gridSizeEpsilon = gridSizeEpsilon;
}


void RayGrid::setRaysGrid()
{
	if (gridSizeBeta <= 0 || gridSizeEpsilon <= 0)
	{
		gridSizeBeta = 1;
		gridSizeEpsilon = 1;
	}

	float delta = 0.000001;
	if (beta <= delta || epsilon <= delta)
	{
		beta = 0.1;
		epsilon = 0.1;
	}

	float betaStep = beta / float(gridSizeBeta); /*<---->*/
	
	float epsilonStep = epsilon / float(gridSizeEpsilon);

	for (int i = -gridSizeEpsilon / 2; i <= gridSizeEpsilon / 2; i++)
	{
		if ((i == 0) && (gridSizeEpsilon % 2 == 0))
			continue;
		for (int j = gridSizeBeta / 2; j >= -gridSizeBeta / 2; j--)
		{
			if ((j == 0) && (gridSizeBeta % 2 == 0))
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

const Matrix3x3 & RayGrid::rotationMatrix() const { return _matrix; }
const vector3f & RayGrid::rotation() const {return _rotation; }
const vector3f & RayGrid::position() const {return _position; }
const vector3f & RayGrid::direction() const { return _direction; }
const std::vector<vector3f> & RayGrid::directions() const { return _directions; }