#pragma once

#include <QtWidgets/QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QImage>
#include <QSplitter>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QPushButton>
#include <QResizeEvent>
#include <QFileDialog>
#include "ui_raytracinggui.h"
#include "objloader.h"
#include "raygrid.h"
#include "imageviewer.h"
#include "visualizator.h"
#include "raytracing.h"
#include "intersectionwizard.h"

class RayTracingGui : public QWidget
{
	Q_OBJECT

public:
	RayTracingGui(QWidget *parent = Q_NULLPTR);

private slots:
	void resizeEvent(QResizeEvent *e);
	void setupVisualizatorWidget();
	void setupControlWidget();
	void setupImageViewer();
	void setupStartParams();
	void calculate();
	void applyGridParams();
	void setCameraControlSlot(QVector3D orig, QVector3D view);

private:
	Ui::RayTracingGuiClass ui;
	ObjLoader loader;
	RayGrid rayGrid;
	ImageViewer *imageViewer;
	QSplitter *splitter;
	RayTracing rayTracing;
	Visualizator vis;
	QWidget *container;

	/*Виджет с элементами управления лучем (позиция и направление)*/
	QWidget controlWidget;
	QDoubleSpinBox xPosSpb;
	QDoubleSpinBox yPosSpb;
	QDoubleSpinBox zPosSpb;
	QDoubleSpinBox yawSpb;
	QDoubleSpinBox pitchSpb;
	QDoubleSpinBox rollSpb;
	QVBoxLayout controlsLayout;

	/*Элементы управления сеткой*/
	QSpinBox xGridSizeSpb;
	QSpinBox yGridSizeSpb;
	QSpinBox gridYawAngleSpb;
	QSpinBox gridPitchAngleSpb;
	QPushButton applyGridParamBtn;

	/*Элементы управления FPS отрисовки изображения*/
	QSpinBox fpsSpb;

	/*Загрузка объекта сцены*/
	QPushButton loadObjBtn;

	/*Параметры сетки лучей*/
	int gridSizeX;
	int gridSizeY;
	int gridYawAngle;
	int gridPitchAngle;

	/*Буффер изображения*/
	std::vector<unsigned char> imageBuffer;

	/*Флаг для блокировки сигналов изменения значений спинбоксов 
	пока все значения не будут установлены*/
	bool blockSpinBoxSignals;
	/*Флаг для контроля минимального FPS отрисовки изображения*/
	bool blockCameraControll;
	QTimer fpsTimer;
	int cameraFPS;
};
