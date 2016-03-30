
#include "main.h"										
#include "obj.h"								
#include "DataAdapter.h"
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

void RenderScene() 
{


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		gluLookAt(8, 0, 0, 0, 1.0f, 0, 1, 0, 0);
		glRotatef(-90, 1.0f, 0, 0);
		glRotatef(g_RotateX, 0, 0, 1.0f);
		g_RotateX += g_RotationSpeed;
		//	glEnable(GL_LIGHTING);
		// ����ģ�������еĶ���
		glLineWidth(3.0f);
		glBegin(GL_LINES);
		// ���ƺ�ɫ��x��
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);

		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);

		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0, -1.0f, 0.0f);

		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);




		// ������ɫ��y��
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 5, 0.0f);
		// ������ɫ��z��
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 5);
		glEnd();
		int CountIndex = 0;
		for (int i = 0; i < g_3DModel.numOfObjects; i++)
		{
			// �������Ĵ�СС��0�����˳�
			if (g_3DModel.pObject.size() <= 0) break;

			// ��õ�ǰ��ʾ�Ķ���
			t3DObject *pObject = &g_3DModel.pObject[i];
			glPointSize(5.0f);
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
			// ��ʼ��g_ViewModeģʽ����
			glBegin(GL_POINTS);	//GL_POINTS g_ViewMode
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
					glColor3f(0.0f, 0.0f, 0.0f);
				//	glColor3f(float((j % 255) / 255), 1.0f - (float(j % 255) / 255), 0.0);
					if (m_DataAdapter.DataIndex[CountIndex] >0 && CountIndex <= 18847)
					{
						glColor3f((float)m_DataAdapter.AddressCode[(m_DataAdapter.DataIndex[CountIndex])].R, (float)m_DataAdapter.AddressCode[m_DataAdapter.DataIndex[CountIndex]].G, (float)m_DataAdapter.AddressCode[m_DataAdapter.DataIndex[CountIndex]].B);
				//		glColor3f(1.0f, 0.0f, 0.0f);
					}
// 					else
// 					{
// 						glColor3f(0.0f, 0.0f, 0.0f);
// 					}
					
					
				//	glColor3f((float)m_DataAdapter.m_parallel3DObj[i].pColors[index].x / 255, (float)m_DataAdapter.m_parallel3DObj[i].pColors[index].y / 255, (float)m_DataAdapter.m_parallel3DObj[i].pColors[index].z / 255);
					glVertex3f(pObject->pVerts[index].x, pObject->pVerts[index].y, pObject->pVerts[index].z);
					CountIndex++;
				}
			}
			CountIndex = 0;
			glEnd();								// ���ƽ���
		}






		for (int i = 0; i < g_3DModel.numOfObjects; i++)
		{
			// �������Ĵ�СС��0�����˳�
			if (g_3DModel.pObject.size() <= 0) break;

			// ��õ�ǰ��ʾ�Ķ���
			t3DObject *pObject = &g_3DModel.pObject[i];
			glPointSize(1.0f);
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
			// ��ʼ��g_ViewModeģʽ����
			glBegin(GL_POINTS);	//GL_POINTS g_ViewMode
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
					glColor3f(1.0f, 1.0f, 1.0f);
					//	glColor3f(float((j % 255) / 255), 1.0f - (float(j % 255) / 255), 0.0);

					// 					else
					// 					{
					// 						glColor3f(0.0f, 0.0f, 0.0f);
					// 					}


					//	glColor3f((float)m_DataAdapter.m_parallel3DObj[i].pColors[index].x / 255, (float)m_DataAdapter.m_parallel3DObj[i].pColors[index].y / 255, (float)m_DataAdapter.m_parallel3DObj[i].pColors[index].z / 255);
					glVertex3f(pObject->pVerts[index].x*1.1, pObject->pVerts[index].y*1.1, pObject->pVerts[index].z*1.1);
					CountIndex++;
				}
			}
			CountIndex = 0;
			glEnd();								// ���ƽ���
		}
		m_DataAdapter.SetDoRead(true);


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

