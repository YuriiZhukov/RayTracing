#include <QDebug>
#include <QtMath>
#include "visualizator.h"

Visualizator::Visualizator()
{
	defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
	rootEntity = new Qt3DCore::QEntity();

	cameraEntity = camera();

	cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 10000.0f);
	cameraEntity->setPosition(QVector3D(-20, 0, 0));
	cameraEntity->setUpVector(QVector3D(0, 1, 0));
	cameraEntity->setViewCenter(QVector3D(0, 0, 0));

	camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
	camController->setCamera(cameraEntity);
	camController->setLinearSpeed(25);

#if SPHERE
	m_sphere = new Qt3DExtras::QSphereMesh();
	m_sphere->setRadius(1.0f);
	m_sphere->setRings(36);
	m_sphere->setSlices(36);

	// Sphere Transform
	m_sphereTransform = new Qt3DCore::QTransform();
	m_sphereTransform->setScale(2.0f);
	m_sphereTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 25.0f));
	m_sphereTransform->setTranslation(QVector3D(5.0f, 4.0f, 0.0f));
	
	Qt3DExtras::QPhongMaterial *m_sphereMaterial = new Qt3DExtras::QPhongMaterial();
	m_sphereMaterial->setDiffuse(QColor(QRgb(0xbeb32b)));

	// Sphere
	m_sphereEntity = new Qt3DCore::QEntity(rootEntity);
	m_sphereEntity->addComponent(m_sphere);
	m_sphereEntity->addComponent(m_sphereMaterial);
	m_sphereEntity->addComponent(m_sphereTransform);
#endif

	line = new LineMesh(rootEntity);
	line->setPoints(QVector3D(0, 0, 0), QVector3D(0, 10, 0));
	line->setColor(QVector3D(0, 1, 0));

	line1 = new LineMesh(rootEntity);
	line1->setPoints(QVector3D(0, 0, 0), QVector3D(10, 0, 0));
	line1->setColor(QVector3D(1, 0, 0));

	line2 = new LineMesh(rootEntity);
	line2->setPoints(QVector3D(0, 0, 0), QVector3D(0, 0, 10));
	line2->setColor(QVector3D(0, 0, 1));

	ray = new LineMesh(rootEntity);
	ray->setPoints(QVector3D(0, 0, 0), QVector3D(10, 10, 10));
	ray->setColor(QVector3D(1, 1, 1));
	ray->setLength(100);

	/*Загрузка obj*/
	objEntity = new Qt3DCore::QEntity(rootEntity);
	objMesh = new Qt3DRender::QMesh(objEntity);
	objMesh->setSource(QUrl::fromLocalFile("cubes.obj"));
	objMsterial = new Qt3DExtras::QPhongMaterial;
	objMsterial->setDiffuse(QColor(QRgb(0xffffff)));
	objEntity->addComponent(objMsterial);
	objEntity->addComponent(objMesh);

	setRootEntity(rootEntity);

	connect(cameraEntity, &Qt3DRender::QCamera::viewVectorChanged, 
		this, &Visualizator::setCameraControl);

	//connect(&fpsTimer, &QTimer::isSingleShot, [this]() {blockCameraControll = false; });
}

void Visualizator::setSphere(int id, QVector3D pos)
{
	spheres[id]->setTranslation(pos);
}

void Visualizator::createSpheres(int count)
{
#if SPHERE_I
	for (int i = 0; i < count; i++)
	{
		Qt3DExtras::QSphereMesh *i_sphere = new Qt3DExtras::QSphereMesh();
		i_sphere->setRadius(0.1f);
		i_sphere->setRings(12);
		i_sphere->setSlices(12);

		// Sphere Transform
		Qt3DCore::QTransform *i_sphereTransform = new Qt3DCore::QTransform();
		i_sphereTransform->setScale(2.0f);
		i_sphereTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 25.0f));
		i_sphereTransform->setTranslation(QVector3D(5.0f, 4.0f, 0.0f));

		Qt3DExtras::QPhongMaterial *i_sphereMaterial = new Qt3DExtras::QPhongMaterial();
		i_sphereMaterial->setDiffuse(QColor(QRgb(0xff0000)));

		// Sphere
		Qt3DCore::QEntity *i_sphereEntity = new Qt3DCore::QEntity(rootEntity);
		i_sphereEntity->addComponent(i_sphere);
		i_sphereEntity->addComponent(i_sphereMaterial);
		i_sphereEntity->addComponent(i_sphereTransform);

		spheres.append(i_sphereTransform);
	}
#endif

}

void Visualizator::load(QString fileName)
{
	objMesh->setSource(QUrl::fromLocalFile(fileName));
}

void Visualizator::setCameraControl()
{
	QVector3D dest = cameraEntity->position() + cameraEntity->viewVector().normalized() * ray->length();
	QVector3D orig = cameraEntity->position() - cameraEntity->viewVector().normalized() * ray->length();
	QVector3D view = cameraEntity->viewVector().normalized();
	
	QQuaternion q = QQuaternion::fromDirection(view, QVector3D(0, 1, 0));
	float yaw, pitch, roll;
	q.getEulerAngles(&pitch, &yaw, &roll);

	QVector3D rot = QVector3D(yaw, pitch, roll);

	ray->setPoints(QVector3D(orig.x(), orig.y() - 0.1, orig.z()), dest);
	m_sphereTransform->setTranslation(dest);
	
	
	/*qDebug() << "Cam: (" << view.x() << ";" 
						 << view.y() << ";" 
						 << view.z() << ")";

	qDebug() << "Rot: (" << (int)rot.x() << ";" 
						 << (int)rot.y() << ";" 
						 << (int)rot.z() << ")";*/

	emit setCameraControlSignal(cameraEntity->position(), rot);
	
}