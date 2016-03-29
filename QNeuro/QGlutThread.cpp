#include "QGlutThread.h"
#include <GL\glut.h>
#define GL_PI 3.1415f
//获取屏幕的宽度
GLint SCREEN_WIDTH1   = 0;
GLint SCREEN_HEIGHT1 = 0;
//设置程序的窗口大小
GLint windowWidth = 640;
GLint windowHeight = 480;
//绕x轴旋转角度
GLfloat xRotAngle = 0.0f;
//绕y轴旋转角度
GLfloat yRotAngle = 0.0f;
//显示回调函数

void renderScreen(void){

	
//	QGlutThread::BindingWindow();
	RenderScene();
	glutPostRedisplay();
	glPopMatrix();
	//交换两个缓冲区的指针
	glutSwapBuffers();
	
}
//设置Redering State 
void setupRederingState(void){
	//设置清理颜色为黑色
	glClearColor(0.0f, 0.0, 0.0, 1.0f);
	//设置绘画颜色为绿色
	glColor3f(0.0f, 1.0f, 0.0f);
}
//窗口大小变化回调函数
void changSize(GLint w, GLint h){
	//横宽比率
// 	GLfloat ratio;
// 	//设置坐标系为x(-100.0f,100.0f)、y(-100.0f,100.0f)、z(-100.0f,100.0f)
// 	GLfloat coordinatesize = 9.0f;
// 	//窗口宽高为零直接返回
// 	if ((w == 0) || (h == 0))
// 		return;
// 	//设置视口和窗口大小一致
// 	glViewport(0, 0, w, h);
// 	//对投影矩阵应用随后的矩阵操作
// 	glMatrixMode(GL_PROJECTION);
// 	//重置当前指定的矩阵为单位矩阵　
// 	glLoadIdentity();
// 	ratio = (GLfloat)w / (GLfloat)h;
// 	//正交投影
// 	if (w < h)
// 		glOrtho(-coordinatesize, coordinatesize, -coordinatesize / ratio, coordinatesize / ratio, -coordinatesize, coordinatesize);
// 	else
// 		glOrtho(-coordinatesize*ratio, coordinatesize*ratio, -coordinatesize, coordinatesize, -coordinatesize, coordinatesize);
// 	//对模型视图矩阵堆栈应用随后的矩阵操作
// 	glMatrixMode(GL_MODELVIEW);
// 	//重置当前指定的矩阵为单位矩阵　
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
	//重新绘制
	glutPostRedisplay();
}

/*Q_OBJECT*/



QGlutThread::QGlutThread(int argc, char* argv[], QWidget *parent /*= 0*/)
{

//	this->setGeometry(0, 0, windowWidth, windowHeight);;
	Init();
		//初始化glut 
	glutInit(&argc, argv);
	//使用双缓冲区模式
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
	//获取系统的宽像素
	SCREEN_WIDTH1 = glutGet(GLUT_SCREEN_WIDTH);
	//获取系统的高像素
	SCREEN_HEIGHT1 = glutGet(GLUT_SCREEN_HEIGHT);
	glutCreateWindow("PointsDemo");
	//设置窗口大小
	glutReshapeWindow(windowWidth, windowHeight);
	//窗口居中显示
//	glutPositionWindow((SCREEN_WIDTH - windowWidth) / 2, (SCREEN_HEIGHT - windowHeight) / 2);
	//窗口大小变化时的处理函数
	glutReshapeFunc(SizeOpenGLScreen);
	//设置显示回调函数 
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
	SetWindowLong(hWnd, GWL_STYLE, style);   //无边框无标题
	SetParent(hWnd, (HWND)this->winId());
	//设置按键输入处理回调函数
	glutSpecialFunc(sPecialkeyFuc);
	//设置全局渲染参数
	setupRederingState();
	glutMainLoop();
	this->exec();
}
