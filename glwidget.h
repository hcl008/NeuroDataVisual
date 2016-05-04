#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL>
#include <QWidget>
#include "MAIN.H"
#include <QTime>

class GLWidget : public QGLWidget
{
	Q_OBJECT
	public slots:
	void drawGL();
public:
	explicit GLWidget(QGLWidget *parent = 0);
	~GLWidget();

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void keyPressEvent(QKeyEvent *e);
	bool fullscreen;

private:
	QWidget *ui;
	QTimer *m_timerOpenGL;
};

#endif // GLWIDGET_H