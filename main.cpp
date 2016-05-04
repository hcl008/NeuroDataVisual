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
<<<<<<< HEAD:QNeuro/main.cpp
// 	w.resize(1800 , 600);
=======
// 	w.resize(1500 , 600);
>>>>>>> 20c52743ecfcbbe87dc1495bdf86c54c3d2379d7:main.cpp
// 	w.show();
	ifstream ReadConfFile;
	QBatExec myExec;

<<<<<<< HEAD:QNeuro/main.cpp
	// 	QMainPanel w1(argc, argv);
	// 	w1.show();
=======
	 	QMainPanel w1(argc, argv);
	 	w1.show();
>>>>>>> 20c52743ecfcbbe87dc1495bdf86c54c3d2379d7:main.cpp


	QGlutThread w(argc,argv);
	w.show();





	return a.exec();
}
