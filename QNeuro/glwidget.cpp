#include "glwidget.h"
//#include "ui_glwidget.h"

#include <QtGui>
#include <QtCore>
#include <QtOpenGL>
#include <GL\GL.h>

void GLWidget::drawGL()
{
	updateGL();
}

GLWidget::GLWidget(QGLWidget *parent) : QGLWidget(parent)
{
//	this->winId();
	
	m_timerOpenGL = new QTimer(this);
	connect(m_timerOpenGL, SIGNAL(timeout()), this, SLOT(drawGL()));
	m_timerOpenGL->start(70);
	setGeometry(50, 30, 640, 480);
}

//这是对虚函数，这里是重写该函数
void GLWidget::initializeGL()
{
	qglClearColor(Qt::white);
	glShadeModel(GL_SMOOTH); // Enables Smooth Shading
	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL); // The Type Of Depth Test To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
	paintGL();
	updateGL();
	//	MainLoop();



}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
	glLoadIdentity(); // Reset The Current Modelview Matrix
	glTranslatef(-1.5, 0.0, -6.0);
	glRotatef(0.0, 0.0, 1.0, 0.0);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, -1.0, -1.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, -1.0, -1.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glEnd();

	glLoadIdentity();
	glTranslatef(1.5, 0.0, -7.0);
	glRotatef(0.0, 1.0, 1.0, 1.0);

	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glColor3f(1.0, 0.5, 0.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glEnd();
	
// 	rTri += 1.2;
// 	rQuad -= 1.15;
}

//该程序是设置opengl场景透视图，程序中至少被执行一次(程序启动时).
void GLWidget::resizeGL(int width, int height)
{
	if (0 == height)
		height = 1;//防止一条边为0
	glViewport(0, 0, (GLint)width, (GLint)height);//重置当前视口，本身不是重置窗口的，只不过是这里被Qt给封装好了
	glMatrixMode(GL_PROJECTION);//选择投影矩阵
	glLoadIdentity();//重置选择好的投影矩阵
	// gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0);//建立透视投影矩阵
	//glMatirxMode(GL_MODELVIEW);//以下2句和上面出现的解释一样
	glLoadIdentity();


}
void GLWidget::keyPressEvent(QKeyEvent *e)
{
	switch (e->key())
	{
		//F1键为全屏和普通屏显示切换键
	case Qt::Key_F1:
		fullscreen = !fullscreen;
		if (fullscreen)
			showFullScreen();
		else
		{
			setGeometry(300, 150, 640, 480);
			showNormal();
		}
		updateGL();
		break;
		//Ese为退出程序键
	case Qt::Key_Escape:
		close();
	}
}

GLWidget::~GLWidget()
{
	
}