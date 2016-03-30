
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

	g_Loadobj.ImportObj(&g_3DModel, FILE_NAME);			// 将obj文件装入到模型结构体中

// 	// 遍历所有的材质
// 	for(int i = 0; i < g_3DModel.numOfMaterials; i++)
// 	{
// 		// 判断是否是一个文件名
// 		if(strlen(g_3DModel.pMaterials[i].strFile) > 0)
// 		{
// 			//  使用纹理文件名称来装入位图
// 			CreateTexture(g_Texture, g_3DModel.pMaterials[i].strFile, i);			
// 		}
// 
// 		// 设置材质的纹理ID
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

	// 遍历场景中所有的对象
// 	for(int i = 0; i < g_3DModel.numOfObjects; i++)
// 	{
// 		// 删除所有的变量
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
		// 遍历模型中所有的对象
		glLineWidth(3.0f);
		glBegin(GL_LINES);
		// 绘制红色的x轴
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




		// 绘制绿色的y轴
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 5, 0.0f);
		// 绘制蓝色的z轴
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 5);
		glEnd();
		int CountIndex = 0;
		for (int i = 0; i < g_3DModel.numOfObjects; i++)
		{
			// 如果对象的大小小于0，则退出
			if (g_3DModel.pObject.size() <= 0) break;

			// 获得当前显示的对象
			t3DObject *pObject = &g_3DModel.pObject[i];
			glPointSize(5.0f);
			// 判断该对象是否有纹理映射
			if (pObject->bHasTexture) {

				// 打开纹理映射

				glEnable(GL_TEXTURE_2D);
				glColor3ub(255, 255, 255);
				glBindTexture(GL_TEXTURE_2D, g_Texture[pObject->materialID]);
			}
			else {

				// 关闭纹理映射
				glDisable(GL_TEXTURE_2D);
				glColor3ub(255, 255, 255);
			}
			// 开始以g_ViewMode模式绘制
			glBegin(GL_POINTS);	//GL_POINTS g_ViewMode
			// 遍历所有的面
			
			for (int j = 0; j < pObject->numOfFaces; j++)
			{
				// 遍历三角形的所有点
				for (int whichVertex = 0; whichVertex < 3; whichVertex++)
				{
					// 获得面对每个点的索引
					int index = pObject->pFaces[j].vertIndex[whichVertex];

					// 给出法向量
					glNormal3f(pObject->pNormals[index].x, pObject->pNormals[index].y, pObject->pNormals[index].z);

					// 如果对象具有纹理
					if (pObject->bHasTexture) {

						// 确定是否有UVW纹理坐标
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
			glEnd();								// 绘制结束
		}






		for (int i = 0; i < g_3DModel.numOfObjects; i++)
		{
			// 如果对象的大小小于0，则退出
			if (g_3DModel.pObject.size() <= 0) break;

			// 获得当前显示的对象
			t3DObject *pObject = &g_3DModel.pObject[i];
			glPointSize(1.0f);
			// 判断该对象是否有纹理映射
			if (pObject->bHasTexture) {

				// 打开纹理映射

				glEnable(GL_TEXTURE_2D);
				glColor3ub(255, 255, 255);
				glBindTexture(GL_TEXTURE_2D, g_Texture[pObject->materialID]);
			}
			else {

				// 关闭纹理映射
				glDisable(GL_TEXTURE_2D);
				glColor3ub(255, 255, 255);
			}
			// 开始以g_ViewMode模式绘制
			glBegin(GL_POINTS);	//GL_POINTS g_ViewMode
			// 遍历所有的面

			for (int j = 0; j < pObject->numOfFaces; j++)
			{
				// 遍历三角形的所有点
				for (int whichVertex = 0; whichVertex < 3; whichVertex++)
				{
					// 获得面对每个点的索引
					int index = pObject->pFaces[j].vertIndex[whichVertex];

					// 给出法向量
					glNormal3f(pObject->pNormals[index].x, pObject->pNormals[index].y, pObject->pNormals[index].z);

					// 如果对象具有纹理
					if (pObject->bHasTexture) {

						// 确定是否有UVW纹理坐标
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
			glEnd();								// 绘制结束
		}
		m_DataAdapter.SetDoRead(true);


//	SwapBuffers(g_hDC);									// 交换缓冲区
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
// 	case WM_LBUTTONDOWN:								// 按下鼠标左键，改变绘制模式
// 		
// 		if(g_ViewMode == GL_TRIANGLES) {		
// 			g_ViewMode = GL_LINE_STRIP;		
// 		} else {
// 			g_ViewMode = GL_TRIANGLES;	
// 		}
// 		break;
// 
// 	case WM_RBUTTONDOWN:								// 按下鼠标右键，改变光照模式
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
// 	case WM_KEYDOWN:									// 键盘响应
// 
// 		switch(wParam) {								
// 			case VK_ESCAPE:								// 按下ESC键
// 				PostQuitMessage(0);					
// 				break;
// 
// 			case VK_LEFT:								// 按下向左键
// 				g_RotationSpeed -= 0.05f;	
// 				break;
// 
// 			case VK_RIGHT:								// 按下向右键
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

