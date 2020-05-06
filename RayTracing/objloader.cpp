#include "objloader.h"
#include <qdebug.h>
#include <algorithm>
#include <qstring.h>

ObjLoader::ObjLoader(){}
ObjLoader::~ObjLoader(){}

bool ObjLoader::load(std::string& filepath)
{
	resetParams();
	qDebug() << QString(filepath.data());
	std::ifstream file;
	file.open(filepath);
	if (!file)
		return false;

	return parseFile(file);
}

void ObjLoader::resetParams()
{
	normals.clear();
	normals.shrink_to_fit();
	vertices.clear();
	vertices.shrink_to_fit();
	indices.clear();
	indices.shrink_to_fit();
	vertexIndices.clear();
	vertexIndices.shrink_to_fit();
	normalIndices.clear();
	normalIndices.shrink_to_fit();
	textureIndices.clear();
	textureIndices.shrink_to_fit();
	_trianglesData.clear();
	_trianglesData.shrink_to_fit();

	faceType = FaceType::unknown;
	pointPerFace = 0;
}

bool ObjLoader::parseFile(std::ifstream& file)
{
	while (!file.eof())
	{
		/*���������� ������ �����*/
		std::string line;
		std::getline(file, line);

		/*������ ������ � �����������*/
		std::istringstream ss(line);
		std::string str;
		ss >> str;

		float x, y, z;

		/*����� ��������� v (���������� �����)*/
		if (str == "v")
		{
			ss >> x; ss >> y; ss >> z;
			vertices.push_back(vector3f(x, y, z));
		}

		/*����� ��������� vn (�������� ������� � �����)*/
		if (str == "vn")
		{
			ss >> x; ss >> y; ss >> z;
			normals.push_back(vector3f(x, y, z));
		}

		/*����� ��������� f (��� ����������� � ������� �� ������)*/
		if (str == "f")
		{
			/*���������� ��������� f*/
			std::string face;

			/*����������� ������� ������ ������������
			(����������� 1 ���) */
			if (faceType == unknown)
			{
				faceType = faceTypeDefinition(line);
				/*��������, ��� ������ ��� ���������*/
				if (faceType == unknown)
					return false;		//����� �� ���������� ��� ������������ ������� ������ ������������
			}

			/*����������� ���������� ����� � ����� �����������
			(�� ������ ���� ���, � ������, ���� ������ ��������������)
			(����������� 1 ���) */ 
			if (pointPerFace == 0)
			{
				pointPerFace = pointPerFaceDefinition(line);
				/*��������, ��� ���-�� ����� ���� ����������*/
				if (pointPerFace != 3)
					return false;		//����� �� ���������� ��� ������������ ���������� ����� �����������
			}

			parseFaceLine(line);
		}
	}
	return fillTrianglesData();
}

FaceType ObjLoader::faceTypeDefinition(std::string & faceline)
{
	std::istringstream ss(faceline);
	std::string s1;

	/*���������� ���� "f" */
	ss >> s1;	 //ss1 = 'f'

	/*���������� ������ ������ ��������*/
	ss >> s1;

	/*�������� �� ��� "������� // �������" */
	int n = s1.find("//", 0);
	if (n != std::string::npos)
		return FaceType::vn;
	/*�������� �� ��� "������� / ���������� ���������� / �������" */
	else n = std::count(s1.begin(), s1.end(), '/');
	if (n == 2)
		return FaceType::vtn;
	/*�������� �� ��� "������� / ���������� ����������" */ //-------����������� ������ ��������!
	else if (n == 1)
		return FaceType::vt;
	
	return FaceType::unknown;
}

unsigned char ObjLoader::pointPerFaceDefinition(std::string & faceline)
{
	/*������� ����� ����� ����������*/
	unsigned char facesPoitntCounter = 0;
	
	std::istringstream ss(faceline);
	std::string s1;
	
	/*���������� ���� "f" */
	ss >> s1;	 //ss1 = 'f'

	while (!ss.eof())
	{
		ss >> s1;
		facesPoitntCounter++;
		/*���-�� ����� ����������� ������ ���� = 3, ����� ������ �� ��������������*/
		if (facesPoitntCounter > 3)
			return facesPoitntCounter;
	}

	return facesPoitntCounter;
}

void ObjLoader::parseFaceLine(std::string & faceline)
{
	std::istringstream ss(faceline);
	std::string s1;
	
	/*���������� ���� "f" */
	ss >> s1;	 //ss1 = 'f'

	if (faceType == FaceType::vn)
	{
		while (!ss.eof())
		{
			std::string group;
			ss >> group;

			int n = group.find("//", 0);
			if (n != std::string::npos)
			{
				/*�������� �������� '//' */
				group.replace(n, 2, " ");
				std::istringstream group_ss(group);
				/*������� ����� � ��������*/
				unsigned int vindex, nindex;
				group_ss >> vindex;
				group_ss >> nindex;
				vertexIndices.push_back(vindex);	//v
				normalIndices.push_back(nindex);	//n
			}
		}
	}
	else if (faceType = FaceType::vtn)
	{
		while (!ss.eof())
		{
			std::string group;
			ss >> group;

			int n = group.find("/", 0);
			if (n != std::string::npos)
			{
				/*�������� �������� '/' */
				group.replace(n, 1, " ");
				std::istringstream group_ss(group);
				/*������� �����, ������� � ��������*/
				unsigned int vindex, tindex, nindex;
				group_ss >> vindex;
				group_ss >> tindex;
				group_ss >> nindex;
				vertexIndices.push_back(vindex);	//v
				textureIndices.push_back(tindex);	//t
				normalIndices.push_back(nindex);	//n
			}
		}
	}
	else if (faceType = FaceType::vt)
	{
		while (!ss.eof())
		{
			std::string group;
			ss >> group;

			int n = group.find("/", 0);
			if (n != std::string::npos)
			{
				/*�������� ������� '/' */
				group.replace(n, 1, " ");
				std::istringstream group_ss(group);
				/*������� ����� �  �������*/
				unsigned int vindex, tindex;
				group_ss >> vindex;
				group_ss >> tindex;
				vertexIndices.push_back(vindex);	//v
				textureIndices.push_back(tindex);	//t
				//����������� ������� ��������
				qDebug() << "ERROR in " << __FUNCTION__"!!!" <<
							"�� ���������� ������� ��������";
			}
		}
	}
}

bool ObjLoader::fillTrianglesData()
{
	if (!checkDataCorrectness())
		return false;

	_trianglesData.resize(vertexIndices.size());
	for (size_t i = 0; i < vertexIndices.size(); i += 3)
	{
		TrianglePoint p0, p1, p2;

		/*������� ����� ���������� � 1. ���������� �������� � 0
		(������ ������� ��������� �� ������� -1)*/
		p0.coords = vertices[vertexIndices[i + 0] - 1];
		p0.normals = normals[normalIndices[i + 0] - 1];

		p1.coords = vertices[vertexIndices[i + 1] - 1];
		p1.normals = normals[normalIndices[i + 1] - 1];

		p2.coords = vertices[vertexIndices[i + 2] - 1];
		p2.normals = normals[normalIndices[i + 2] - 1];

		_trianglesData[i] = TriangleData(p0, p1, p2);
	}
	
	IntersectionWizard& iw = IntersectionWizard::getInstance();
	iw.setObjData(_trianglesData);
	
	return true;
}

bool ObjLoader::checkDataCorrectness()
{
	if (vertexIndices.size() != normalIndices.size())
	{
		qDebug() << "ERROR in " << __FUNCTION__"!!!" << 
					"Different vector size (vertexIndices != normalIndices)";
		return false;
	}
	/*�������� �������� ���� ��������*/
	if (vertexIndices.size() == 0 || normalIndices.size() == 0 ||
		vertices.size() == 0 || normals.size() == 0)
	{
		qDebug() << "ERROR in " << __FUNCTION__"!!!" <<
					"Elements count in vector = 0";
		return false;
	}

	/*��������, ��� ������������ ������ ���������/�������� �� ������
	������� ���� ��������� ���������/�������� � �����*/
	int maxVertexIndex = *std::max_element(vertexIndices.begin(), vertexIndices.end());
	int maxNormalIndex = *std::max_element(normalIndices.begin(), normalIndices.end());
	if (maxVertexIndex != vertices.size() || maxNormalIndex != normals.size())
	{
		qDebug() << "ERROR in " << __FUNCTION__"!!!" <<
					"Elements count in vectors and does not match";
		return false;
	}

	return true;
}

std::vector<TriangleData>& ObjLoader::trianglesData() { return _trianglesData; }
