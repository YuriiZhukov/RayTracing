#include "raytracinggui.h"

RayTracingGui::RayTracingGui(QWidget *parent)
	: QWidget(parent), blockSpinBoxSignals(false), 
	blockCameraControll(false), cameraFPS(30)
{
	ui.setupUi(this);
	splitter = new QSplitter(this);
	setupVisualizatorWidget();
	setupControlWidget();
	setupImageViewer();
	
	loader.load(std::string("cub2es.obj"));
	vis.load("cubes.obj");

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

	loadObjBtn.setText(QString("Load '.obj'"));
	connect(&loadObjBtn, &QPushButton::clicked, [this]()
	{
		QString fileName = QFileDialog::getOpenFileName(this,
			tr("Open Obj"), "", tr("Image Files (*.obj)"));
		if (fileName != "")
		{
			loader.load(fileName.toStdString());
			vis.load(fileName);
		}
	});
	controlsLayout.addWidget(&loadObjBtn);

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
	/*ќграничение ширины виджета управлени€ в 100 пикселей*/
	controlWidget.setMaximumWidth(100);
	controlWidget.setLayout(&controlsLayout);
	splitter->addWidget(&controlWidget);
}

void RayTracingGui::setupStartParams()
{
	fpsSpb.setMinimum(1);
	fpsSpb.setMaximum(1000);
	fpsSpb.setValue(30);

	xGridSizeSpb.setMinimum(1);	   yGridSizeSpb.setMinimum(1);
	xGridSizeSpb.setMaximum(1000); yGridSizeSpb.setMaximum(1000);
	xGridSizeSpb.setValue(250);	   yGridSizeSpb.setValue(250);

	gridYawAngleSpb.setMinimum(1);	  gridPitchAngleSpb.setMinimum(1);
	gridYawAngleSpb.setMaximum(180);  gridPitchAngleSpb.setMaximum(180);
	gridYawAngleSpb.setValue(70);	  gridPitchAngleSpb.setValue(70);

	this->applyGridParams();
}

void RayTracingGui::applyGridParams()
{
	gridSizeX = xGridSizeSpb.value();
	gridSizeY = yGridSizeSpb.value();
	gridYawAngle = gridYawAngleSpb.value();
	gridPitchAngle = gridPitchAngleSpb.value();
	rayGrid.setGrid(deg2rad(gridYawAngleSpb.value()), deg2rad(gridPitchAngleSpb.value()), gridSizeX, gridSizeY);
	this->calculate();
}

void RayTracingGui::calculate()
{
	if (loader.trianglesData().size() == 0)
		return;

	rayGrid.setPosition(xPosSpb.value(), yPosSpb.value(), zPosSpb.value());
	rayGrid.setRotation(deg2rad(yawSpb.value()), deg2rad(pitchSpb.value()), deg2rad(rollSpb.value()));

	/*¬ектор дл€ записи выходных точек пересечени€*/
	std::vector<vector3f> points;
	/*¬ектор дл€ записи выходных дальностей до точек пересечени€*/
	std::vector<float> lengths;

	IntersectionWizard& iw = IntersectionWizard::getInstance();
	iw.setObjData(loader.trianglesData());
	iw.setDirData(rayGrid.directions());
	iw.setOrigData(rayGrid.position());

	rayTracing.calculate(loader.trianglesData(), rayGrid.directions(),
						 rayGrid.position(), points, lengths,
						 gridSizeX, gridSizeY);
	float maxLen = 0.0;
	float minLen = lengths[0];
	for (int i = 0; i < lengths.size(); i++)
	{
		if (lengths[i] > maxLen)
			maxLen = lengths[i];
		if (lengths[i] < minLen)
			minLen = lengths[i];
	}
	/*ѕостроение изображени€ в соответствии с количеством заданных лучей направлений*/
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
	QImage image(&imageBuffer[0], gridSizeX, gridSizeY, QImage::Format_RGB32);
	imageViewer->setImage(image);


}

void RayTracingGui::setCameraControlSlot(QVector3D orig, QVector3D view)
{
	if (blockCameraControll)
		return;
	/*«аблокировать сигналы*/
	blockSpinBoxSignals = true;
	xPosSpb.setValue(orig.x());
	yPosSpb.setValue(orig.y());
	zPosSpb.setValue(orig.z());
	yawSpb.setValue(view.x());
	pitchSpb.setValue(view.y());
	rollSpb.setValue(view.z());
	this->calculate();
	/*–азблокировать сигналы*/
	blockSpinBoxSignals = false;

	/*Ѕлокировка отрисовки на заданный FPS*/
	fpsTimer.singleShot(1000 / cameraFPS, [this]() {blockCameraControll = false; });
	blockCameraControll = true;

}

void RayTracingGui::resizeEvent(QResizeEvent *e)
{
	splitter->resize(this->size());
}