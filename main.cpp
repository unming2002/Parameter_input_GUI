#include "CMain.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CMain w;
	w.show();

	return a.exec();
}
