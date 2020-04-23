#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QImage>
#include <QScrollArea>
#include <QWheelEvent>
#include <QLabel>

class ImageViewer : public QScrollArea
{
	Q_OBJECT

public:
	ImageViewer();
	void setImage(const QImage &newImage);

private:
	void normalSize();
	void wheelEvent(QWheelEvent *e);
	void scaleImage(double factor);

private:
	QImage image;
	QLabel *imageLabel;
	double scaleFactor;
};

#endif
