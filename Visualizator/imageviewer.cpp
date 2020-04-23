
#include "imageviewer.h"

ImageViewer::ImageViewer(): imageLabel(new QLabel), 
	scaleFactor(1.0)
{
	imageLabel->setScaledContents(true);
	setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	setWidget(imageLabel);
	setImage(image);
}

void ImageViewer::setImage(const QImage &newImage)
{
	image = newImage;
	imageLabel->setPixmap(QPixmap::fromImage(image));
	normalSize();
}

void ImageViewer::normalSize()
{
	imageLabel->adjustSize();
	scaleFactor = 1.0;
}

void ImageViewer::scaleImage(double factor)
{
	imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());
}

void ImageViewer::wheelEvent(QWheelEvent *e)
{
	if (e->angleDelta().y() > 0)
		scaleFactor += 0.1;
	else
		scaleFactor -= 0.1;

	if (scaleFactor <= 0.0)
		scaleFactor = 0.1;
	
	scaleImage(scaleFactor);
}
