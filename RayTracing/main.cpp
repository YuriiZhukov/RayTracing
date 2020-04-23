#include "raytracing.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RayTracing w;
	return a.exec();
}
