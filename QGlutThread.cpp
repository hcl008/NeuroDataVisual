#include "QGlutThread.h"
#include <GL\glut.h>
#define GL_PI 3.1415f
//��ȡ��Ļ�Ŀ��
GLint SCREEN_WIDTH1   = 0;
GLint SCREEN_HEIGHT1 = 0;
//���ó���Ĵ��ڴ�С
GLint windowWidth = 640;
GLint windowHeight = 480;
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

//	this->setGeometry(0, 0, windowWidth, windowHeight);;
	Init();
		//��ʼ��glut 
	glutInit(&argc, argv);
	//ʹ��˫������ģʽ
	this->start();
	


//	this->start();
}

QGlutThread::~QGlutThread()
{

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
