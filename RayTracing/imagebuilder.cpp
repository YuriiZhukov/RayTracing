#include "imagebuilder.h"
#include <algorithm>

ImageBuilder::ImageBuilder() : image(nullptr), viewDistance(50.0) {}
ImageBuilder::~ImageBuilder(){}

QImage & ImageBuilder::createImage(std::vector<float>& lengths)
{
	if (image)
	{
		delete image;
		image = nullptr;
	}

	IntersectionWizard& iw = IntersectionWizard::getInstance();
	if (!iw.dataCorrect())
		return QImage();

	std::for_each(lengths.begin(), lengths.end(), [this](float& l)
	{
		l = (l > viewDistance ? viewDistance : l) / viewDistance * 255.0;
	});

	int sizeX = iw.gridData().raysByYaw;
	int sizeY = iw.gridData().raysByPitch;

	/*Построение изображения в соответствии с количеством заданных лучей направлений*/
	const int imageBufferSize = 4 * sizeX * sizeY;
	imageBuffer.clear();
	imageBuffer.shrink_to_fit();
	imageBuffer.resize(imageBufferSize);

	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			int pixelPos = i * sizeX + j;
			int pixelColor = 255.0 - lengths[pixelPos];
			imageBuffer[4 * pixelPos + 0] = pixelColor;
			imageBuffer[4 * pixelPos + 1] = pixelColor;
			imageBuffer[4 * pixelPos + 2] = pixelColor;
		}
	}
	image = new QImage(&imageBuffer[0], sizeX, sizeY, QImage::Format_RGB32);
	return *image;
}

void ImageBuilder::setViewDistance(int value)
{
	viewDistance = value;
}