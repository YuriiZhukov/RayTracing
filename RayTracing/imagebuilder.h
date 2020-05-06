#pragma once

#include <QObject>
#include <QImage>
#include "intersectionwizard.h"

class ImageBuilder : public QObject
{
	Q_OBJECT

public:
	ImageBuilder();
	~ImageBuilder();

	QImage& createImage(std::vector<float>& lengths);
	void setViewDistance(int value);

private:
	QImage *image;
	/*Буффер изображения*/
	std::vector<unsigned char> imageBuffer;
	/*Дальность видимости при отрисовке изображения*/
	float viewDistance;

};
