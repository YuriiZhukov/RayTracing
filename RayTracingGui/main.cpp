#include "raytracinggui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RayTracingGui w;
	w.show();
	return a.exec();
}
