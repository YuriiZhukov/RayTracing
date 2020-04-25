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
#include <QRadioButton>
#include <QButtonGroup>
#include "ui_raytracinggui.h"
#include "objloader.h"
#include "ray.h"
#include "imageviewer.h"
#include "visualizator.h"
#include "raytracing.h"
#include "intersectionwizard.h"
#include "imagebuilder.h"

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
	Ray ray;
	ImageViewer *imageViewer;
	QSplitter *splitter;
	RayTracing rayTracing;
	Visualizator vis;
	ImageBuilder imageBuilder;
	QWidget *container;

	/*¬иджет с элементами управлени€ лучем (позици€ и направление)*/
	QWidget controlWidget;
	QDoubleSpinBox xPosSpb;
	QDoubleSpinBox yPosSpb;
	QDoubleSpinBox zPosSpb;
	QDoubleSpinBox yawSpb;
	QDoubleSpinBox pitchSpb;
	QDoubleSpinBox rollSpb;
	QVBoxLayout controlsLayout;

	/*Ёлементы управлени€ сеткой*/
	QSpinBox xGridSizeSpb;
	QSpinBox yGridSizeSpb;
	QSpinBox gridYawAngleSpb;
	QSpinBox gridPitchAngleSpb;
	QPushButton applyGridParamBtn;

	/*Ёлементы управлени€ дл€ параметров расчета*/
	QButtonGroup deviceBtnGroup;
	QButtonGroup matrixBtnGroup;
	QRadioButton gpuRbtn;
	QRadioButton cpuRbtn;
	QRadioButton matrixRbtn;
	QRadioButton quaternionRbtn;

	/*Ёлементы управлени€ FPS отрисовки изображени€*/
	QSpinBox fpsSpb;

	/*«агрузка объекта сцены*/
	QPushButton loadObjBtn;

	/*‘лаг дл€ блокировки сигналов изменени€ значений спинбоксов 
	пока все значени€ не будут установлены*/
	bool blockSpinBoxSignals;
	/*‘лаг дл€ контрол€ минимального FPS отрисовки изображени€*/
	bool blockCameraControll;
	QTimer fpsTimer;
	int cameraFPS;

	/*‘лаг дл€ расчета на CUDA*/
	bool CUDA_CALC;
};
