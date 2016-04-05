#pragma once
#include <QtOpenGL>
#include <QWidget>
#include "MAIN.H"
#include <QTimer>
#include <QThread>
#include <GL\glut.h>
#include <QEvent>
#include "DataAdapter.h"
#include <fstream>
class QGlutThread : public QWidget, public QThread
{
	Q_OBJECT
// 		public slots:
// 		void timerDone();
public:
	QGlutThread( int argc, char* argv[], QWidget *parent = 0);
	~QGlutThread();
/*	QTimer * BindingTimer;*/
	static QGlutThread * currentInstance;
	void resizeEvent(QResizeEvent *);
	void run();

private:
	
};
