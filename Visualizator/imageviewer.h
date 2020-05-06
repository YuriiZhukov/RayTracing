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
	/*Усановить изображение в виджет*/
	void setImage(const QImage &newImage);

private:
	/*Оригинальный размер изображения*/
	void normalSize();
	/*СКМ мыши*/
	void wheelEvent(QWheelEvent *e);
	/*ПКМ мыши*/
	void mousePressEvent(QMouseEvent *e);
	/*Масштабирование изображения*/
	void scaleImage(double factor);
	/*Создание контекстного меню ПКМ*/
	void createContextMenu();
	/*Сохранение изображения в формате PNG*/
	void saveImage();
	/*Показать контекстное меню*/
	void showContextMenu(QPoint pos);

private:
	QImage image;
	QLabel *imageLabel;
	double scaleFactor;

	/*Меню ПКМ*/
	QMenu contextMenu;
	QAction saveImageAction;
};

#endif
