#include "raytracinggui.h"
#include <QtWidgets/QApplication>
#include <bitset>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RayTracingGui w;
	w.show();
	return a.exec();
}
