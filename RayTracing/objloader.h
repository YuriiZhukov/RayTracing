#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "structs.h"
#include "intersectionwizard.h"

class ObjLoader
{
public:
	ObjLoader();
	virtual ~ObjLoader();
	bool load(std::string & filepath);
	std::vector<TriangleData> & trianglesData();

private:
	/*����� ���������� ����� ����� ���������*/
	void resetParams();
	/*���� ����� obj*/
	bool parseFile(std::ifstream& file);
	/*����������� ������� ������� ������������ � ����� obj*/
	FaceType faceTypeDefinition(std::string & faceline);
	/*����������� ��������� ����� �� ������ ����������� � ����� obj*/
	unsigned char pointPerFaceDefinition(std::string & faceline);
	/*���� ������ � ��������� ����������� � ����� obj*/
	void parseFaceLine(std::string & faceline);
	/*���������� ������ ���� ������������� �������*/
	bool fillTrianglesData();
	/*�������� ������������ �������� �� ������������ ����� */
	bool checkDataCorrectness();

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

