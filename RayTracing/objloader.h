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
	/*Сброс параметров перед новой загрузкой*/
	void resetParams();
	/*Парс файла obj*/
	bool parseFile(std::ifstream& file);
	/*Определение способа задания поверхностей в файле obj*/
	FaceType faceTypeDefinition(std::string & faceline);
	/*Определение количеств точек на каждую поверхность в файле obj*/
	unsigned char pointPerFaceDefinition(std::string & faceline);
	/*Парс строки с описанием поверхности в файле obj*/
	void parseFaceLine(std::string & faceline);
	/*Заполнение данных всех треугольников объекта*/
	bool fillTrianglesData();
	/*Проверка корректности массивов из прочитанного файла */
	bool checkDataCorrectness();

private:
	/*Вектор значений нормалей каждой точки*/
	std::vector<vector3f> normals;
	/*Вектор значений координат каждой точки*/
	std::vector<vector3f> vertices;
	/*Вектор значений индексов каждой точки*/
	std::vector<unsigned int> indices;
	/*Тип поверхности по умолчанию*/
	FaceType faceType;
	/*Кол-во точек на поверхности по умолчанию*/
	unsigned char pointPerFace;
	/*Вектор индексов нормалей для поверхностей*/
	std::vector<unsigned int> normalIndices;
	/*Вектор индексов точек для поверхностей*/
	std::vector<unsigned int> vertexIndices;
	/*Вектор индексов текстур для поверхностей*/ //заполняется, но не используется
	std::vector<unsigned int> textureIndices;
	/*Данные всех треугольников объекта*/
	std::vector<TriangleData> _trianglesData;
};

