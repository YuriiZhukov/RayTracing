#include "imagebuilder.h"

ImageBuilder::ImageBuilder() : image(nullptr){}
ImageBuilder::~ImageBuilder(){}

QImage & ImageBuilder::createImage(std::vector<float>& lengths)
{
	if (image)
	{
		delete image;
		image = nullptr;
	}

	IntersectionWizard& iw = IntersectionWizard::getInstance();

	float maxLen = 0.0;
	float minLen = lengths[0];
	for (int i = 0; i < lengths.size(); i++)
	{
		if (lengths[i] > maxLen)
			maxLen = lengths[i];
		if (lengths[i] < minLen)
			minLen = lengths[i];
	}

	int gridSizeX = iw.gridData().raysByYaw;
	int gridSizeY = iw.gridData().raysByPitch;

	/*Построение изображения в соответствии с количеством заданных лучей направлений*/
	const int imageBufferSize = 4 * gridSizeX * gridSizeY;
	imageBuffer.clear();
	imageBuffer.resize(imageBufferSize);
	//unsigned char *imageBuffer = new unsigned char[imageBufferSize];
	for (int i = 0; i < gridSizeY; i++)
	{
		for (int j = 0; j < gridSizeX; j++)
		{
			int pixelPos = i * gridSizeX + j;
			int pixelColor = fabs((lengths[pixelPos] / maxLen * 255) - 255.0);
			imageBuffer[4 * pixelPos + 0] = pixelColor;
			imageBuffer[4 * pixelPos + 1] = pixelColor;
			imageBuffer[4 * pixelPos + 2] = pixelColor;
		}
	}
	image = new QImage(&imageBuffer[0], gridSizeX, gridSizeY, QImage::Format_RGB32);
	return *image;
}
