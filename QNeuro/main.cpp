#include "glwidget.h"
#include <QtWidgets/QApplication>
#include "MAIN.H"
#include "QGlutThread.h"
#include "OriginalData.h"
#include <fstream>
#include "QBatExec.h"
#include "QMainPanel.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
/*	Init();*/
//	GLWidget w;
// 	w.resize(1800 , 600);
// 	w.show();
	ifstream ReadConfFile;
	QBatExec myExec;

	// 	QMainPanel w1(argc, argv);
	// 	w1.show();


	QGlutThread w(argc,argv);
	w.show();





	return a.exec();
}
