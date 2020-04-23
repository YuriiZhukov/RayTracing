#pragma once

#include <QtGui/QScreen>

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qaspectengine.h>

#include <Qt3DRender/qcamera.h>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qcameralens.h>
#include <Qt3DRender/qrenderaspect.h>

#include <Qt3DInput/QInputAspect>

#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>

#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QMesh>

#include <QTimer>

#include "linemesh.h"

#define SPHERE 1
#define SPHERE_I 1

class Visualizator : public Qt3DExtras::Qt3DWindow
{
	Q_OBJECT

public:
	Visualizator();
	void setSphere(int id, QVector3D pos);
	void createSpheres(int count);
	void load(QString fileName);

private slots:
	void setCameraControl();
	
signals:
	void setCameraControlSignal(QVector3D pos, QVector3D dest);

private:
	Qt3DCore::QEntity *rootEntity;
	Qt3DRender::QCamera *cameraEntity;
	Qt3DExtras::QFirstPersonCameraController *camController;

#if SPHERE
	Qt3DExtras::QSphereMesh *m_sphere;
	Qt3DCore::QEntity *m_sphereEntity;
	Qt3DCore::QTransform *m_sphereTransform;
#endif

#if SPHERE_I
	QVector<Qt3DCore::QTransform*> spheres;
#endif

	Qt3DCore::QEntity *objEntity;
	Qt3DRender::QMesh *objMesh;
	Qt3DExtras::QPhongMaterial *objMsterial;

	LineMesh *line;
	LineMesh *line1;
	LineMesh *line2;
	LineMesh *ray;

};
