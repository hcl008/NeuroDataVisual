#include "glwidget.h"
#include <QtWidgets/QApplication>
#include "MAIN.H"
#include "QGlutThread.h"
#include "OriginalData.h"
#include <fstream>
#include "QBatExec.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
/*	Init();*/
//	GLWidget w;
// 	w.resize(800 , 600);
// 	w.show();
	ifstream ReadConfFile;
	QBatExec myExec;

	QGlutThread w(argc,argv);
	w.show();
	return a.exec();
}
