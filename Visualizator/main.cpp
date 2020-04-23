#include "visualizator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Visualizator w;
	w.show();
	return a.exec();
}
