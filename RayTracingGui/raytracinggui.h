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
#include "imageviewer.h"
#include "visualizator.h"
#include "raytracing.h"
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
	ImageViewer *imageViewer;
	QSplitter *splitter;
	RayTracing rayTracing;
	Visualizator vis;
	ImageBuilder imageBuilder;
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

	/*Элементы управления для параметров расчета*/
	QButtonGroup deviceBtnGroup;
	QButtonGroup matrixBtnGroup;
	QRadioButton gpuRbtn;
	QRadioButton cpuRbtn;
	QRadioButton matrixRbtn;
	QRadioButton quaternionRbtn;

	/*Элементы управления FPS отрисовки изображения*/
	QSpinBox fpsSpb;

	/*Загрузка объекта сцены*/
	QPushButton loadObjBtn;

	/*Дальность видимости*/
	QSpinBox viewDistanceSpb;

	/*Флаг для блокировки сигналов изменения значений спинбоксов 
	пока все значения не будут установлены*/
	bool blockSpinBoxSignals;
	/*Флаг для контроля минимального FPS отрисовки изображения*/
	bool blockCameraControll;
	QTimer fpsTimer;
	int cameraFPS;

	/*Флаг для расчета на CUDA*/
	bool CUDA_CALC;
};
