#include "raytracinggui.h"
#include <QElapsedTimer>

RayTracingGui::RayTracingGui(QWidget *parent)
	: QWidget(parent), blockSpinBoxSignals(false),
	blockCameraControll(false), cameraFPS(30), CUDA_CALC(true)
{
	ui.setupUi(this);
	splitter = new QSplitter(this);
	setupVisualizatorWidget();
	setupControlWidget();
	setupImageViewer();
	
	rayTracing.load(std::string("landscape.obj"));
	vis.load("landscape.obj");

	setupStartParams();

	connect(&vis, &Visualizator::setCameraControlSignal,
		this, &RayTracingGui::setCameraControlSlot);
}

void RayTracingGui::setupVisualizatorWidget()
{
	container = createWindowContainer(&vis);
	splitter->addWidget(container);
}

void RayTracingGui::setupImageViewer()
{
	imageViewer = new ImageViewer();
	splitter->addWidget(imageViewer);
}

void RayTracingGui::setupControlWidget()
{
	auto setRow = [this](QDoubleSpinBox* spb, QLabel* lbl)
	{
		QHBoxLayout *lay = new QHBoxLayout;
		spb->setMinimum(-10000.0);
		spb->setMaximum(10000.0);

		lay->addWidget(lbl);
		lay->addWidget(spb);
		controlsLayout.addLayout(lay);

		connect(spb, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [this](double value)
		{
			if (!blockSpinBoxSignals)
				this->calculate();
		});
	};

	auto setGridRow = [this](QSpinBox* spb, QLabel* lbl)
	{
		QHBoxLayout *lay = new QHBoxLayout;

		lay->addWidget(lbl);
		lay->addWidget(spb);
		controlsLayout.addLayout(lay);
	};

	auto setRadioRow = [this](QRadioButton* rbtn, const QString& text)
	{
		QHBoxLayout *lay = new QHBoxLayout;
		rbtn->setText(text);
		lay->addWidget(rbtn);
		controlsLayout.addLayout(lay);
	};

	gpuRbtn.setChecked(true);

	deviceBtnGroup.addButton(&gpuRbtn);
	deviceBtnGroup.addButton(&cpuRbtn);	

	setRadioRow(&gpuRbtn, "CUDA calculation");
	setRadioRow(&cpuRbtn, "CPU calculation");
	connect(&cpuRbtn, &QRadioButton::clicked, [this]()
	{
		CUDA_CALC = false;
	});	
	connect(&gpuRbtn, &QRadioButton::clicked, [this]()
	{
		CUDA_CALC = true;
	});

	loadObjBtn.setText(QString("Load '.obj'"));
	connect(&loadObjBtn, &QPushButton::clicked, [this]()
	{
		QString fileName = QFileDialog::getOpenFileName(this,
			tr("Open Obj"), "", tr("Image Files (*.obj)"));
		if (fileName != "")
		{
			rayTracing.load(fileName.toStdString());			
			vis.load(fileName);
		}
	});
	controlsLayout.addWidget(&loadObjBtn);

	setGridRow(&viewDistanceSpb, new QLabel("View distance:"));
	connect(&viewDistanceSpb, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		[this](int value) 
	{
		imageBuilder.setViewDistance(value); 
		this->calculate();
	});

	setGridRow(&fpsSpb, new QLabel("FPS:"));
	connect(&fpsSpb, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		[this](int value) {cameraFPS = value; });

	setGridRow(&xGridSizeSpb, new QLabel("Size X:"));
	setGridRow(&yGridSizeSpb, new QLabel("Size Y:"));
	setGridRow(&gridYawAngleSpb, new QLabel("Yaw radius:"));
	setGridRow(&gridPitchAngleSpb, new QLabel("Pitch radius:"));
	
	applyGridParamBtn.setText(QString("Apply"));
	connect(&applyGridParamBtn, &QPushButton::clicked, [this]()
	{
		this->applyGridParams();
	});
	controlsLayout.addWidget(&applyGridParamBtn);

	setRow(&xPosSpb, new QLabel("X:"));
	setRow(&yPosSpb, new QLabel("Y:"));
	setRow(&zPosSpb, new QLabel("Z:"));
	setRow(&yawSpb, new QLabel("Yaw:"));
	setRow(&pitchSpb, new QLabel("Pitch:"));
	setRow(&rollSpb, new QLabel("Roll:"));
	/*Ограничение ширины виджета управления в 150 пикселей*/
	controlWidget.setMaximumWidth(150);
	controlWidget.setLayout(&controlsLayout);
	splitter->addWidget(&controlWidget);
}

void RayTracingGui::setupStartParams()
{
	fpsSpb.setMinimum(1);
	fpsSpb.setMaximum(1000);
	fpsSpb.setValue(30);

	xGridSizeSpb.setMinimum(1);	   yGridSizeSpb.setMinimum(1);
	xGridSizeSpb.setMaximum(4096); yGridSizeSpb.setMaximum(4096);
	xGridSizeSpb.setValue(250);	   yGridSizeSpb.setValue(250);

	gridYawAngleSpb.setMinimum(1);	  gridPitchAngleSpb.setMinimum(1);
	gridYawAngleSpb.setMaximum(180);  gridPitchAngleSpb.setMaximum(180);
	gridYawAngleSpb.setValue(70);	  gridPitchAngleSpb.setValue(70);

	viewDistanceSpb.setMinimum(1);
	viewDistanceSpb.setMaximum(10000);
	viewDistanceSpb.setValue(100);

	this->applyGridParams();
}

void RayTracingGui::applyGridParams()
{
	//vis.createSpheres(25);
	rayTracing.setRaysGrid(deg2rad(gridYawAngleSpb.value()),
						   deg2rad(gridPitchAngleSpb.value()),
						   xGridSizeSpb.value(), yGridSizeSpb.value());
	imageBuilder.setViewDistance(viewDistanceSpb.value());
	this->calculate();
}

void RayTracingGui::calculate()
{
	QElapsedTimer totalTmr;
	QElapsedTimer tmr;

	totalTmr.start();

	tmr.start();
	rayTracing.setRayPosition(xPosSpb.value(), yPosSpb.value(), zPosSpb.value());
	quint64 timeToPosition = tmr.elapsed();

	tmr.start();
	rayTracing.setRayRotation(deg2rad(yawSpb.value()), deg2rad(pitchSpb.value()), deg2rad(rollSpb.value()));
	quint64 timeToRotation = tmr.elapsed();

	/*Вектор для записи выходных точек пересечения*/
	std::vector<vector3f> points;
	/*Вектор для записи выходных дальностей до точек пересечения*/
	std::vector<float> lengths;

	tmr.start();
	if (CUDA_CALC)
		rayTracing.calculate(points, lengths);
	else
		rayTracing.calculate_cpu(points, lengths);
	quint64 timeToCalculate = tmr.elapsed();

//	for (int i = 0; i < points.size(); i++)
//		vis.setSphere(i, QVector3D(points[i].x, points[i].y, points[i].z));
	
	tmr.start();
	imageViewer->setImage(imageBuilder.createImage(lengths));
	quint64 timeToImage = tmr.elapsed();

	quint64 totalTime = totalTmr.elapsed();

	qDebug() << "Posit ms = " << timeToPosition;
	qDebug() << "Rotat ms = " << timeToRotation;
	qDebug() << "Calc  ms = " << timeToCalculate;
	qDebug() << "Image ms = " << timeToImage;
	qDebug() << "Total ms = " << totalTime << "\n";
}

void RayTracingGui::setCameraControlSlot(QVector3D orig, QVector3D view)
{
	if (blockCameraControll)
		return;

	/*Заблокировать сигналы*/
	blockSpinBoxSignals = true;
	xPosSpb.setValue(orig.x());
	yPosSpb.setValue(orig.y());
	zPosSpb.setValue(orig.z());
	yawSpb.setValue(view.x());
	pitchSpb.setValue(view.y());
	rollSpb.setValue(view.z());
	/*Разблокировать сигналы*/
	blockSpinBoxSignals = false;
	
	this->calculate();

	/*Блокировка отрисовки на заданный FPS*/
	fpsTimer.singleShot(1000 / cameraFPS, [this]() {blockCameraControll = false; });
	blockCameraControll = true;
}

void RayTracingGui::resizeEvent(QResizeEvent *e)
{
	splitter->resize(this->size());
}