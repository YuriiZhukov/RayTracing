#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QImage>
#include <QScrollArea>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QMenu>

class ImageViewer : public QScrollArea
{
	Q_OBJECT

public:
	ImageViewer();
	/*��������� ����������� � ������*/
	void setImage(const QImage &newImage);

private:
	/*������������ ������ �����������*/
	void normalSize();
	/*��� ����*/
	void wheelEvent(QWheelEvent *e);
	/*��� ����*/
	void mousePressEvent(QMouseEvent *e);
	/*��������������� �����������*/
	void scaleImage(double factor);
	/*�������� ������������ ���� ���*/
	void createContextMenu();
	/*���������� ����������� � ������� PNG*/
	void saveImage();
	/*�������� ����������� ����*/
	void showContextMenu(QPoint pos);

private:
	QImage image;
	QLabel *imageLabel;
	double scaleFactor;

	/*���� ���*/
	QMenu contextMenu;
	QAction saveImageAction;
};

#endif
