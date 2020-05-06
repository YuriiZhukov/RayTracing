#include <QFileDialog>
#include "imageviewer.h"

ImageViewer::ImageViewer(): imageLabel(new QLabel), 
	scaleFactor(1.0)
{
	imageLabel->setScaledContents(true);
	setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	setWidget(imageLabel);
	setImage(image);
	createContextMenu();
}

void ImageViewer::createContextMenu()
{
	saveImageAction.setText("Save as PNG");
	contextMenu.addAction(&saveImageAction);
	connect(&saveImageAction, &QAction::triggered, this, &ImageViewer::saveImage);
}

void ImageViewer::showContextMenu(QPoint pos)
{
	contextMenu.exec(mapToGlobal(pos));
}

void ImageViewer::setImage(const QImage &newImage)
{
	image = newImage;
	imageLabel->setPixmap(QPixmap::fromImage(image));
	scaleImage(scaleFactor);
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

void ImageViewer::saveImage()
{
	QString fileName = QFileDialog::getSaveFileName(this,
			 tr("Save as PNG"),"untitled", tr("Images (*.png)"));
	if (fileName != "")
		image.save(fileName);
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

void ImageViewer::mousePressEvent(QMouseEvent *e)
{
	if (e->type() == Qt::RightButton)
		showContextMenu(e->pos());
}
