#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "structs.h"

class ObjLoader
{
public:
	ObjLoader();
	virtual ~ObjLoader();
	void load(std::string & filepath);
	void setPosition(float x, float y, float z);
	void setRotation(float yaw, float pithc, float roll);
	std::vector<TriangleData> & trianglesData();

private:
	/*����� ���������� ����� ����� ���������*/
	void resetParams();
	/*���� ����� obj*/
	void parseFile(std::ifstream& file);
	/*����������� ������� ������� ������������ � ����� obj*/
	FaceType faceTypeDefinition(std::string & faceline);
	/*����������� ��������� ����� �� ������ ����������� � ����� obj*/
	unsigned char pointPerFaceDefinition(std::string & faceline);
	/*���� ������ � ��������� ����������� � ����� obj*/
	void parseFaceLine(std::string & faceline);
	/*���������� ������ ���� ������������� �������*/
	void fillTrianglesData();

private:
	/*������ �������� �������� ������ �����*/
	std::vector<vector3f> normals;
	/*������ �������� ��������� ������ �����*/
	std::vector<vector3f> vertices;
	/*������ �������� �������� ������ �����*/
	std::vector<unsigned int> indices;
	/*��� ����������� �� ���������*/
	FaceType faceType;
	/*���-�� ����� �� ����������� �� ���������*/
	unsigned char pointPerFace;
	/*������ �������� �������� ��� ������������*/
	std::vector<unsigned int> normalIndices;
	/*������ �������� ����� ��� ������������*/
	std::vector<unsigned int> vertexIndices;
	/*������ �������� ������� ��� ������������*/ //�����������, �� �� ������������
	std::vector<unsigned int> textureIndices;
	/*������ ���� ������������� �������*/
	std::vector<TriangleData> _trianglesData;
};

