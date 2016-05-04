
#include "main.h"										
#include "obj.h"								
#include "DataAdapter.h"
#include "AQWidgetFrameless.h"
#include <exception>
<<<<<<< HEAD:QNeuro/obj_main.cpp
#include <fstream>
ofstream ofile;
=======

>>>>>>> 20c52743ecfcbbe87dc1495bdf86c54c3d2379d7:obj_main.cpp
bool  g_bFullScreen = true;								
HWND  g_hWnd;											
RECT  g_rRect;											
HDC   g_hDC;											
HGLRC g_hRC;											
HINSTANCE g_hInstance;									


#define FILE_NAME  "foot.obj"							

UINT g_Texture[MAX_TEXTURES] = {0};						

CLoadObj g_Loadobj;									
t3DModel g_3DModel;									

int   g_ViewMode = GL_TRIANGLES;//GL_LINE_STRIP;
bool  g_bLighting     = true;		
float g_RotateX		  = 0.0f;		
float g_RotationSpeed = 0.1f;		

DataAdapter m_DataAdapter;
void Init()
{
// 	g_hWnd = hWnd;										
// 	GetClientRect(g_hWnd, &g_rRect);					
// 	InitializeOpenGL(g_rRect.right, g_rRect.bottom);

	g_Loadobj.ImportObj(&g_3DModel, FILE_NAME);			// ��obj�ļ�װ�뵽ģ�ͽṹ����

// 	// �������еĲ���
// 	for(int i = 0; i < g_3DModel.numOfMaterials; i++)
// 	{
// 		// �ж��Ƿ���һ���ļ���
// 		if(strlen(g_3DModel.pMaterials[i].strFile) > 0)
// 		{
// 			//  ʹ�������ļ�������װ��λͼ
// 			CreateTexture(g_Texture, g_3DModel.pMaterials[i].strFile, i);			
// 		}
// 
// 		// ���ò��ʵ�����ID
// 		g_3DModel.pMaterials[i].texureId = i;
// 	}

	glEnable(GL_LIGHT0);								
	glEnable(GL_LIGHTING);								
	glEnable(GL_COLOR_MATERIAL);					

}

void MainLoop()
{
	/*MSG msg;*/
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
// 	while(1)											
// 	{													 
			RenderScene();						

/*	}*/

	// �������������еĶ���
// 	for(int i = 0; i < g_3DModel.numOfObjects; i++)
// 	{
// 		// ɾ�����еı���
// 		delete [] g_3DModel.pObject[i].pFaces;
// 		delete [] g_3DModel.pObject[i].pNormals;
// 		delete [] g_3DModel.pObject[i].pVerts;
// 		delete [] g_3DModel.pObject[i].pTexVerts;
// 	}

//	DeInit();	

}



<<<<<<< HEAD:QNeuro/obj_main.cpp
#define MAX_CHAR       128

void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) { // ����ǵ�һ�ε��ã�ִ�г�ʼ��
		// Ϊÿһ��ASCII�ַ�����һ����ʾ�б�
		isFirstCall = 0;

		// ����MAX_CHAR����������ʾ�б���
		lists = glGenLists(MAX_CHAR);

		// ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}
void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}
=======

>>>>>>> 20c52743ecfcbbe87dc1495bdf86c54c3d2379d7:obj_main.cpp
void RenderScene() 
{

	ofile.open("vertexInfo.txt");
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		
		gluLookAt(12.0f, 0, 0,    0, 0.0f, 0,    1, 1, 0);

		glRotatef(-90, 1.0f, 0, 0);
		glRotatef(g_RotateX, 0.0f, 0.0f, 1.0f);
		g_RotateX += g_RotationSpeed;
		//	glEnable(GL_LIGHTING);
		// ����ģ�������еĶ���
// 		glLineWidth(3.0f);
// 		glBegin(GL_LINES);
// 		// ���ƺ�ɫ��x��
// 		glColor3f(1.f, 0.f, 0.f);
// 		glVertex3f(-1.0f, 1.0f, 0.0f);
// 		glVertex3f(1.0f, 1.0f, 0.0f);
// 
// 		glColor3f(1.f, 0.f, 0.f);
// 		glVertex3f(1.0f, 1.0f, 0.0f);
// 		glVertex3f(1.0f, -1.0f, 0.0f);
// 
// 		glColor3f(1.f, 0.f, 0.f);
// 		glVertex3f(-1.0f, -1.0f, 0.0f);
// 		glVertex3f(1.0, -1.0f, 0.0f);
// 
// 		glColor3f(1.f, 0.f, 0.f);
// 		glVertex3f(-1.0f, 1.0f, 0.0f);
// 		glVertex3f(-1.0f, -1.0f, 0.0f);

// 		// ������ɫ��y��
// 		glColor3f(0.f, 1.f, 0.f);
// 		glVertex3f(0.0f, 0.0f, 0.0f);
// 		glVertex3f(0.0f, 5, 0.0f);
// 		// ������ɫ��z��
// 		glColor3f(0.f, 0.f, 1.f);
// 		glVertex3f(0.0f, 0.0f, 0.0f);
// 		glVertex3f(0.0f, 0.0f, 5);
// 		glEnd();
		
	//	glLoadIdentity();
//		glViewport(0, 0, 800, 600);
// 		glMatrixMode(GL_PROJECTION);
// 		glLoadIdentity();
/*		glFrustum(-1.5f, 1.5, -1.0f, 1, 1.5, 20);//����һ��͸����ͼƽ ��ͷ��*/
	//	glFrustum(-1.5*(GLfloat)750 / (GLfloat)410, 1.5*(GLfloat)750 / (GLfloat)410, -1.5*(GLfloat)750 / (GLfloat)410, 1.5*(GLfloat)750 / (GLfloat)410, -150.0, 150.0);

<<<<<<< HEAD:QNeuro/obj_main.cpp
		glEnable(GL_BLEND);        // �򿪻��
		glDisable(GL_DEPTH_TEST);    // �ر���Ȳ���
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
=======
		
>>>>>>> 20c52743ecfcbbe87dc1495bdf86c54c3d2379d7:obj_main.cpp
		int CountIndex = 0;
		for (int i = 0; i < g_3DModel.numOfObjects; i++)
		{
			// �������Ĵ�СС��0�����˳�
			if (g_3DModel.pObject.size() <= 0) break;

			// ��õ�ǰ��ʾ�Ķ���
			t3DObject *pObject = &g_3DModel.pObject[i];
<<<<<<< HEAD:QNeuro/obj_main.cpp
			glPointSize(3.0f);
=======
			glPointSize(1.0f);
>>>>>>> 20c52743ecfcbbe87dc1495bdf86c54c3d2379d7:obj_main.cpp
			// �жϸö����Ƿ�������ӳ��
			if (pObject->bHasTexture) {

				// ������ӳ��

				glEnable(GL_TEXTURE_2D);
				glColor3ub(255, 255, 255);
				glBindTexture(GL_TEXTURE_2D, g_Texture[pObject->materialID]);
			}
			else {

				// �ر�����ӳ��
				glDisable(GL_TEXTURE_2D);
				glColor3ub(255, 255, 255);
			}
<<<<<<< HEAD:QNeuro/obj_main.cpp
			glLineWidth(2.0f);
			glEnable(GL_LINE_SMOOTH);
			// ��ʼ��g_ViewModeģʽ����
			glBegin(GL_LINE_STRIP);	//GL_POINTS g_ViewMode
			
=======
			
			// ��ʼ��g_ViewModeģʽ����
			glBegin(GL_LINES);	//GL_POINTS g_ViewMode
>>>>>>> 20c52743ecfcbbe87dc1495bdf86c54c3d2379d7:obj_main.cpp
			// �������е���
			
			for (int j = 0; j < pObject->numOfFaces; j++)
			{
				// ���������ε����е�
				for (int whichVertex = 0; whichVertex < 3; whichVertex++)
				{
					// ������ÿ���������
					int index = pObject->pFaces[j].vertIndex[whichVertex];

					// ����������
					glNormal3f(pObject->pNormals[index].x, pObject->pNormals[index].y, pObject->pNormals[index].z);

					// ��������������
					if (pObject->bHasTexture) {

						// ȷ���Ƿ���UVW��������
						if (pObject->pTexVerts) {
							glTexCoord2f(pObject->pTexVerts[index].x, pObject->pTexVerts[index].y);
						}
					}
					else {

						if (g_3DModel.pMaterials.size() && pObject->materialID >= 0)
						{
							BYTE *pColor = g_3DModel.pMaterials[pObject->materialID].color;
							glColor3ub(pColor[0], pColor[1], pColor[2]);
						}
					}
					glColor4f(0.0f, 0.0f, 0.0f,0.0f);
				//	glColor3f(float((j % 255) / 255), 1.0f - (float(j % 255) / 255), 0.0);
					if (m_DataAdapter.DataIndex[CountIndex] >0 && CountIndex <= 18847)
					{
<<<<<<< HEAD:QNeuro/obj_main.cpp
						glColor4f((float)m_DataAdapter.AddressCode[(m_DataAdapter.DataIndex[CountIndex])].R, (float)m_DataAdapter.AddressCode[m_DataAdapter.DataIndex[CountIndex]].G, (float)m_DataAdapter.AddressCode[m_DataAdapter.DataIndex[CountIndex]].B,0.5f);
				//		glColor3f(1.0f, 0.0f, 0.0f);
					}
					else
					{
						glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
					}


			//		ofile << "CountIndex: " << index << "  Object: " <<i<< endl;
=======
						glColor3f((float)m_DataAdapter.AddressCode[(m_DataAdapter.DataIndex[CountIndex])].R, (float)m_DataAdapter.AddressCode[m_DataAdapter.DataIndex[CountIndex]].G, (float)m_DataAdapter.AddressCode[m_DataAdapter.DataIndex[CountIndex]].B);
				//		glColor3f(1.0f, 0.0f, 0.0f);
					}
// 					else
// 					{
// 						glColor3f(0.0f, 0.0f, 0.0f);
// 					}
					
>>>>>>> 20c52743ecfcbbe87dc1495bdf86c54c3d2379d7:obj_main.cpp
					
				//	glColor3f((float)m_DataAdapter.m_parallel3DObj[i].pColors[index].x / 255, (float)m_DataAdapter.m_parallel3DObj[i].pColors[index].y / 255, (float)m_DataAdapter.m_parallel3DObj[i].pColors[index].z / 255);
					try
					{
						glVertex3f(pObject->pVerts[index].x, pObject->pVerts[index].y, pObject->pVerts[index].z);
					}
					catch (exception *e)
					{
						return;
					}
					CountIndex++;
				}
			}
			CountIndex = 0;
			glEnd();								// ���ƽ���
		}
//		glViewport(750, 0, 800, 610);
		glEnable(GL_BLEND);        // �򿪻��
		glDisable(GL_DEPTH_TEST);    // �ر���Ȳ���
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);



		for (int i = 0; i < g_3DModel.numOfObjects; i++)
		{
			// �������Ĵ�СС��0�����˳�
			if (g_3DModel.pObject.size() <= 0) break;

			// ��õ�ǰ��ʾ�Ķ���
			t3DObject *pObject = &g_3DModel.pObject[i];
			glPointSize(1.0f);
// 			// �жϸö����Ƿ�������ӳ��
// 			if (pObject->bHasTexture) {
// 
// 				// ������ӳ��
// 
// 				glEnable(GL_TEXTURE_2D);
// 				glColor3ub(255, 255, 255);
// 				glBindTexture(GL_TEXTURE_2D, g_Texture[pObject->materialID]);
// 			}
// 			else {
// 
// 				// �ر�����ӳ��
// 				glDisable(GL_TEXTURE_2D);
// 				glColor3ub(255, 255, 255);
// 			}
			// ��ʼ��g_ViewModeģʽ����
			glBegin(GL_TRIANGLE_STRIP);	//GL_POINTS g_ViewMode
			// �������е���

			for (int j = 0; j < pObject->numOfFaces; j++)
			{
				// ���������ε����е�
				for (int whichVertex = 0; whichVertex < 3; whichVertex++)
				{
					// ������ÿ���������
					int index = pObject->pFaces[j].vertIndex[whichVertex];

					// ����������
			//		glNormal3f(pObject->pNormals[index].x, pObject->pNormals[index].y, pObject->pNormals[index].z);

// 					// ��������������
// 					if (pObject->bHasTexture) {
// 
// 						// ȷ���Ƿ���UVW��������
// 						if (pObject->pTexVerts) {
// 							glTexCoord2f(pObject->pTexVerts[index].x, pObject->pTexVerts[index].y);
// 						}
// 					}
// 					else {
// 
// 						if (g_3DModel.pMaterials.size() && pObject->materialID >= 0)
// 						{
// 							BYTE *pColor = g_3DModel.pMaterials[pObject->materialID].color;
// 							glColor3ub(pColor[0], pColor[1], pColor[2]);
// 						}
// 					}
<<<<<<< HEAD:QNeuro/obj_main.cpp
					glColor4f(0.10f, 0.10f, 0.3f,0.1f);
=======
					glColor4f(0.30f, 0.30f, 1.0f,0.1f);
>>>>>>> 20c52743ecfcbbe87dc1495bdf86c54c3d2379d7:obj_main.cpp
					//	glColor3f(float((j % 255) / 255), 1.0f - (float(j % 255) / 255), 0.0);

					// 					else
					// 					{
					// 						glColor3f(0.0f, 0.0f, 0.0f);
					// 					}

					try
					{
						glVertex3f(pObject->pVerts[index].x, pObject->pVerts[index].y, pObject->pVerts[index].z);
					}
					catch (exception* e)
					{
						return;
					}
					//	glColor3f((float)m_DataAdapter.m_parallel3DObj[i].pColors[index].x / 255, (float)m_DataAdapter.m_parallel3DObj[i].pColors[index].y / 255, (float)m_DataAdapter.m_parallel3DObj[i].pColors[index].z / 255);
					
					CountIndex++;
				}
			}
			CountIndex = 0;
			glEnd();								// ���ƽ���
		}
<<<<<<< HEAD:QNeuro/obj_main.cpp
//		glClear(GL_COLOR_BUFFER_BIT);
		selectFont(32, ANSI_CHARSET, "Comic Sans MS");  
		glColor3f(1.0f, 0.0f, 0.0f);
		glRasterPos3f(1.0f, 1.0f,-2.0f);
		string PlotStr = "Index: ";
		char temp[20];
		itoa(m_DataAdapter.CurrentFrameIndex,temp,10); 
		PlotStr += temp;
		drawString(PlotStr.c_str());
=======
>>>>>>> 20c52743ecfcbbe87dc1495bdf86c54c3d2379d7:obj_main.cpp
		if (AQWidgetFrameless::DisplayStatus == START)
		{
			m_DataAdapter.SetDoRead(true);
		}
		if (AQWidgetFrameless::DisplayStatus == STOP)
		{
			m_DataAdapter.SetDoRead(true);
			AQWidgetFrameless::DisplayStatus = PAUSE;
			m_DataAdapter.CurrentFrameIndex = 0;
		}
<<<<<<< HEAD:QNeuro/obj_main.cpp
=======

>>>>>>> 20c52743ecfcbbe87dc1495bdf86c54c3d2379d7:obj_main.cpp

//		ofile.close();
//	SwapBuffers(g_hDC);									// ����������
}

// LRESULT CALLBACK WinProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
// {
//     LONG    lRet = 0; 
//     PAINTSTRUCT    ps;
// 
//     switch (uMsg)
// 	{ 
//     case WM_SIZE:							
// 		if(!g_bFullScreen)				
// 		{
// 			SizeOpenGLScreen(LOWORD(lParam),HIWORD(lParam));
// 			GetClientRect(hWnd, &g_rRect);				
// 		}
//         break; 
//  
// 	case WM_PAINT:									
// 		BeginPaint(hWnd, &ps);						
// 		EndPaint(hWnd, &ps);					
// 		break;
// 
// 	case WM_LBUTTONDOWN:								// �������������ı����ģʽ
// 		
// 		if(g_ViewMode == GL_TRIANGLES) {		
// 			g_ViewMode = GL_LINE_STRIP;		
// 		} else {
// 			g_ViewMode = GL_TRIANGLES;	
// 		}
// 		break;
// 
// 	case WM_RBUTTONDOWN:								// ��������Ҽ����ı����ģʽ
// 		
// 		g_bLighting = !g_bLighting;		
// 
// 		if(g_bLighting) {					
// 			glEnable(GL_LIGHTING);			
// 		} else {
// 			glDisable(GL_LIGHTING);			
// 		}
// 		break;
// 
// 	case WM_KEYDOWN:									// ������Ӧ
// 
// 		switch(wParam) {								
// 			case VK_ESCAPE:								// ����ESC��
// 				PostQuitMessage(0);					
// 				break;
// 
// 			case VK_LEFT:								// ���������
// 				g_RotationSpeed -= 0.05f;	
// 				break;
// 
// 			case VK_RIGHT:								// �������Ҽ�
// 				g_RotationSpeed += 0.05f;			
// 				break;
// 		}
// 		break;
// 
//     case WM_CLOSE:									
//         PostQuitMessage(0);						
//         break; 
//      
//     default:										
//         lRet = DefWindowProc (hWnd, uMsg, wParam, lParam); 
//         break; 
//     } 
//  
//     return lRet;										
// }

