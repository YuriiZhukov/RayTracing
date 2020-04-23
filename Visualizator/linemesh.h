#pragma once

#include <QObject>
#include <Qt3DCore/qentity.h>
#include <QVector3D>

#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QBuffer>
#include <Qt3DExtras/QPerVertexColorMaterial>

class LineMesh : public Qt3DCore::QEntity
{
	Q_OBJECT

public:
	LineMesh(Qt3DCore::QEntity *parent);
	~LineMesh();
	void setPoints(QVector3D &position, QVector3D &view);
	void setColor(QVector3D &color);
	void setLength(float len);
	float length();

private:
	void updateIndexBufferData();
	void updateVertexBufferData();
	void updateColorBufferData();

private:
	Qt3DCore::QEntity *lineEntity;
	Qt3DRender::QGeometryRenderer *customMeshRenderer;
	Qt3DRender::QGeometry *customGeometry;
	Qt3DRender::QBuffer *vertexDataBuffer;
	Qt3DRender::QBuffer *indexDataBuffer;
	Qt3DRender::QBuffer *colorDataBuffer;
	Qt3DRender::QAttribute *positionAttribute;
	Qt3DRender::QAttribute *indexAttribute;
	Qt3DRender::QAttribute *colorAttribute;
	Qt3DExtras::QPerVertexColorMaterial *material;

	QVector<QVector3D> vertices;
	QVector<QVector3D> colors;
	QVector<unsigned int> indices;

	QByteArray vertexBufferData;
	QByteArray indexBufferData;
	QByteArray colorBufferData;

	QVector3D p0;
	QVector3D p1;

	QVector3D p0c;
	QVector3D p1c;

	float _length;

};
