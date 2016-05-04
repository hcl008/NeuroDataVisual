#pragma once
#include <QtOpenGL>
#include <QWidget>
#include "MAIN.H"
#include <QTimer>
#include <QThread>
#include <GL\glut.h>
#include <QEvent>

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPlainTextEdit>

#include "DataAdapter.h"
#include <fstream>
#include "AQWidgetFrameless.h"

class QGlutThread : public QWidget, public QThread
{
	Q_OBJECT
 		public slots:
/* 		void timerDone();*/
public:
	QGlutThread( int argc, char* argv[], QWidget *parent = 0);
	~QGlutThread();
	QTimer * BindingTimer;
	static QGlutThread * currentInstance;
	void resizeEvent(QResizeEvent *);
	void run();
	QWidget *GluWidget;

	void timerEvent(QTimerEvent *event);

	int m_nTimerId;



private:
	QPushButton * m_pButtonStart;
	QPushButton * m_pButtonPause;


};
