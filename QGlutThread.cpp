#include "QGlutThread.h"
#include <GL\glut.h>
#define GL_PI 3.1415f
//��ȡ��Ļ�Ŀ��
GLint SCREEN_WIDTH1   = 0;
GLint SCREEN_HEIGHT1 = 0;
//���ó���Ĵ��ڴ�С
<<<<<<< HEAD:QNeuro/QGlutThread.cpp
GLint windowWidth = 1780;
GLint windowHeight = 680;
=======
GLint windowWidth = 1500;
GLint windowHeight = 500;
>>>>>>> 20c52743ecfcbbe87dc1495bdf86c54c3d2379d7:QGlutThread.cpp
//��x����ת�Ƕ�
GLfloat xRotAngle = 0.0f;
//��y����ת�Ƕ�
GLfloat yRotAngle = 0.0f;
//��ʾ�ص�����

void renderScreen(void){


		//	QGlutThread::BindingWindow();
	
	
		RenderScene();
		glutPostRedisplay();
		glPopMatrix();
		//����������������ָ��
		glutSwapBuffers();
		

	
}
//����Redering State 
void setupRederingState(void){
	//����������ɫΪ��ɫ
	glClearColor(0.0f, 0.0, 0.0, 1.0f);
	//���û滭��ɫΪ��ɫ
	glColor3f(0.0f, 1.0f, 0.0f);
}
//���ڴ�С�仯�ص�����
void changSize(GLint w, GLint h){
	//������
// 	GLfloat ratio;
// 	//��������ϵΪx(-100.0f,100.0f)��y(-100.0f,100.0f)��z(-100.0f,100.0f)
// 	GLfloat coordinatesize = 9.0f;
// 	//���ڿ��Ϊ��ֱ�ӷ���
// 	if ((w == 0) || (h == 0))
// 		return;
// 	//�����ӿںʹ��ڴ�Сһ��
// 	glViewport(0, 0, w, h);
// 	//��ͶӰ����Ӧ�����ľ������
// 	glMatrixMode(GL_PROJECTION);
// 	//���õ�ǰָ���ľ���Ϊ��λ����
// 	glLoadIdentity();
// 	ratio = (GLfloat)w / (GLfloat)h;
// 	//����ͶӰ
// 	if (w < h)
// 		glOrtho(-coordinatesize, coordinatesize, -coordinatesize / ratio, coordinatesize / ratio, -coordinatesize, coordinatesize);
// 	else
// 		glOrtho(-coordinatesize*ratio, coordinatesize*ratio, -coordinatesize, coordinatesize, -coordinatesize, coordinatesize);
// 	//��ģ����ͼ�����ջӦ�����ľ������
// 	glMatrixMode(GL_MODELVIEW);
// 	//���õ�ǰָ���ľ���Ϊ��λ����
// 	glLoadIdentity();
	SizeOpenGLScreen(w,h);

}




void sPecialkeyFuc(int key, int x, int y){

	if (key == GLUT_KEY_UP){
		xRotAngle -= 5.0f;
	}
	else if (key == GLUT_KEY_DOWN){
		xRotAngle += 5.0f;
	}
	else if (key == GLUT_KEY_LEFT){
		yRotAngle -= 5.0f;
	}
	else if (key == GLUT_KEY_RIGHT){
		yRotAngle += 5.0f;
	}
	//���»���
	glutPostRedisplay();
}

/*Q_OBJECT*/



QGlutThread::QGlutThread(int argc, char* argv[], QWidget *parent /*= 0*/)
{
	
<<<<<<< HEAD:QNeuro/QGlutThread.cpp
	

//	this->setWindowFlags(Qt::SubWindow | Qt::FramelessWindowHint);
	m_nTimerId = QWidget::startTimer(30);
=======
	this->setWindowFlags(Qt::WindowSystemMenuHint);
	this->setWindowFlags(Qt::FramelessWindowHint);
	m_nTimerId = QWidget::startTimer(100);
>>>>>>> 20c52743ecfcbbe87dc1495bdf86c54c3d2379d7:QGlutThread.cpp
	this->setGeometry(AQWidgetFrameless::cPos.x(), AQWidgetFrameless::cPos.y(), windowWidth, windowHeight);
// 	GluWidget = new QWidget();
// 	GluWidget->setGeometry(0, 0, 640, 320);
// 	QPushButton *startBtn = new QPushButton(tr("Start Simulation"));
// 	QPushButton *stopBtn = new QPushButton(tr("Stop Simulation"));
// 	QPlainTextEdit *output = new QPlainTextEdit;
// 
// 	QVBoxLayout *mainLayout = new QVBoxLayout;
// 	QHBoxLayout *container = new QHBoxLayout;
// 	QVBoxLayout *consoleLayout = new QVBoxLayout;
// 
// 	
// 	consoleLayout->addWidget(startBtn, 1);
// 	consoleLayout->addWidget(stopBtn, 1);
// //	consoleLayout->addWidget(this, 1);
// 	
// 	GluWidget->setLayout(consoleLayout);
// // 	container->addWidget(consoleWidget, 1);
// 	container->addWidget(this, 4);
// 
// 	QWidget *w = new QWidget;
// 	w->setLayout(container);
// 	mainLayout->addWidget(w, 3);
// 	mainLayout->addWidget(output, 1);
<<<<<<< HEAD:QNeuro/QGlutThread.cpp


=======


>>>>>>> 20c52743ecfcbbe87dc1495bdf86c54c3d2379d7:QGlutThread.cpp
/*	this->setGeometry(0, 0, windowWidth, windowHeight);;*/
// 	BindingTimer = new QTimer();
// 	QWidget::connect(BindingTimer, SIGNAL(timeout()), (QWidget *)this, SLOT(timerDone()));
	
	
/*	BindingTimer->start(30);*/
	Init();
		//��ʼ��glut 
	glutInit(&argc, argv);
	//ʹ��˫������ģʽ
	this->start();
	


//	this->start();
}
// void QGlutThread::timerDone()
// {
// 	int a = 0;
// }
void QGlutThread::timerEvent(QTimerEvent *event)
{
	if (AQWidgetFrameless::SysStatus == CLOSE_APP)
	{
		this->close();
	}
	
	else if (AQWidgetFrameless::SysStatus == MINIMIZE_APP)
	{
		
		this->showMinimized();
	}
// 	if (AQWidgetFrameless::SysSubStatus == AWAKE_APP)
// 	{
// 		this->showNormal();
// 		AQWidgetFrameless::SysSubStatus = NORMAL_APP;
// 	/*	AQWidgetFrameless::SysStatus = NORMAL_APP;*/
// 	}


<<<<<<< HEAD:QNeuro/QGlutThread.cpp
	QPoint X_Increamental(140, 40);
	QPoint thisPos = AQWidgetFrameless::cPos + X_Increamental;
//		this->move(thisPos);
=======
	QPoint X_Increamental(0, 40);
	QPoint thisPos = AQWidgetFrameless::cPos + X_Increamental;
		this->move(thisPos);
>>>>>>> 20c52743ecfcbbe87dc1495bdf86c54c3d2379d7:QGlutThread.cpp
		this->raise();
	//qDebug("timer event, id %d", event->timerId());

}
QGlutThread::~QGlutThread()
{
	if (m_nTimerId != 0)

		QWidget::killTimer(m_nTimerId);
}

void QGlutThread::resizeEvent(QResizeEvent *)
{
	SizeOpenGLScreen(this->width(), this->height());
//	SizeOpenGLScreen(this->width(), this->height());
}

// void QGlutThread::BindingWindow()
// {
// 	int a = 0;
// 
// }

void QGlutThread::run()
{
	

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//��ȡϵͳ�Ŀ�����
	SCREEN_WIDTH1 = glutGet(GLUT_SCREEN_WIDTH);
	//��ȡϵͳ�ĸ�����
	SCREEN_HEIGHT1 = glutGet(GLUT_SCREEN_HEIGHT);
	glutCreateWindow("PointsDemo");
	//���ô��ڴ�С
	glutReshapeWindow(windowWidth, windowHeight);
	//���ھ�����ʾ
//	glutPositionWindow((SCREEN_WIDTH - windowWidth) / 2, (SCREEN_HEIGHT - windowHeight) / 2);
	//���ڴ�С�仯ʱ�Ĵ�����
	glutReshapeFunc(SizeOpenGLScreen);
	//������ʾ�ص����� 
	glutDisplayFunc(renderScreen);
//	glEnable(GL_LIGHTING);
	
//	SetupDrawCallback();
	LONG style; HWND hWnd;
	////////////////////////////////////// 
	hWnd = FindWindow(NULL, L"PointsDemo");
	// 	if (!hWnd)
	// 		cout << "NO!" << endl;

	style = GetWindowLong(hWnd, GWL_STYLE);
	style = style & (~WS_CAPTION) & ~(WS_BORDER)& ~WS_THICKFRAME;
	SetWindowLong(hWnd, GWL_STYLE, style);   //�ޱ߿��ޱ���
	SetParent(hWnd, (HWND)this->winId());
	//���ð������봦��ص�����
	glutSpecialFunc(sPecialkeyFuc);
	//����ȫ����Ⱦ����
	setupRederingState();
	glutMainLoop();
	this->exec();
}
