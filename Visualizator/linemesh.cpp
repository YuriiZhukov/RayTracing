#include "linemesh.h"

LineMesh::LineMesh(Qt3DCore::QEntity *parent)
	: Qt3DCore::QEntity(parent), _length(10.0)
{
	lineEntity = new Qt3DCore::QEntity(parent);
	material = new Qt3DExtras::QPerVertexColorMaterial(lineEntity);
	customMeshRenderer = new Qt3DRender::QGeometryRenderer;
	customGeometry = new Qt3DRender::QGeometry(customMeshRenderer);

	vertexDataBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, customGeometry);
	colorDataBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, customGeometry);
	indexDataBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer, customGeometry);

	p0 = QVector3D(0, 0, 0);
	p1 = QVector3D(_length, 0, 0);

	p0c = QVector3D(1, 1, 1);
	p1c = QVector3D(1, 1, 1);

	vertices << p0 << p1;
	colors << p0c << p1c;

	// Attributes
	positionAttribute = new Qt3DRender::QAttribute();
	positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
	positionAttribute->setBuffer(vertexDataBuffer);
	positionAttribute->setDataType(Qt3DRender::QAttribute::Float);
	positionAttribute->setDataSize(3);
	positionAttribute->setCount(2);
	positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
	
	colorAttribute = new Qt3DRender::QAttribute();
	colorAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
	colorAttribute->setBuffer(colorDataBuffer);
	colorAttribute->setDataType(Qt3DRender::QAttribute::Float);
	colorAttribute->setDataSize(3);
	colorAttribute->setCount(2);
	colorAttribute->setName(Qt3DRender::QAttribute::defaultColorAttributeName());

	indexAttribute = new Qt3DRender::QAttribute();
	indexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
	indexAttribute->setBuffer(indexDataBuffer);
	indexAttribute->setDataType(Qt3DRender::QAttribute::UnsignedInt);
	indexAttribute->setDataSize(1);
	indexAttribute->setCount(2);

	customGeometry->addAttribute(positionAttribute);
	customGeometry->addAttribute(indexAttribute);
	customGeometry->addAttribute(colorAttribute);

	customMeshRenderer->setInstanceCount(1);
	customMeshRenderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
	customMeshRenderer->setGeometry(customGeometry);

	lineEntity->addComponent(customMeshRenderer);
	lineEntity->addComponent(material);

	updateIndexBufferData();
	updateVertexBufferData();
	updateColorBufferData();
}

void LineMesh::updateIndexBufferData()
{
	indexBufferData.resize(2 * sizeof(unsigned int));
	unsigned int *rawIndexArray = reinterpret_cast<unsigned int *>(indexBufferData.data());
	rawIndexArray[0] = 0;
	rawIndexArray[1] = 1;
	indexDataBuffer->setData(indexBufferData);
}

void LineMesh::updateVertexBufferData()
{
	vertexBufferData.resize(2 * 3 * sizeof(float));
	float *rawVertexArray = reinterpret_cast<float *>(vertexBufferData.data());
	int idx = 0; 
	for(const QVector3D &v : vertices) {
		rawVertexArray[idx++] = v.x();
		rawVertexArray[idx++] = v.y();
		rawVertexArray[idx++] = v.z();
	}
	vertexDataBuffer->setData(vertexBufferData);
}

void LineMesh::updateColorBufferData()
{
	colorBufferData.resize(2 * 3 * sizeof(float));
	float *rawColorArray = reinterpret_cast<float *>(colorBufferData.data());
	int idx = 0;
	for (const QVector3D &c : colors) {
		rawColorArray[idx++] = c.x();
		rawColorArray[idx++] = c.y();
		rawColorArray[idx++] = c.z();
	}
	colorDataBuffer->setData(colorBufferData);
}

void LineMesh::setColor(QVector3D &color)
{
	p0c = color;
	p1c = color;
	colors.clear();
	colors << p0c << p1c;
	updateColorBufferData();
}

void LineMesh::setLength(float len)
{
	this->_length = len;
}

float LineMesh::length()
{
	return this->_length;
}

void LineMesh::setPoints(QVector3D &position, QVector3D &view)
{
	p0 = position;
	p1 = view;
	vertices.clear();
	vertices << p0 << p1;
	updateVertexBufferData();
}

LineMesh::~LineMesh()
{

}
