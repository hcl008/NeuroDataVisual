#include "DataAdapter.h"
const int VertexNum[] = { 7207, 141, 3276, 1410, 2072, 114, 1683, 2944 };
inline int TotalVertexNum()
{
	int count = 0;
	for (int i = 0; i < OBJ_NUM; i++)
	{
		count += VertexNum[i];
	}
	return count;
}
DataAdapter::DataAdapter()
{
	m_parallel3DObj = new t3DParallelColor[OBJ_NUM];
	DataIndex = new int[18847];//18847 = total point number in brain obj
	for (int i = 0; i < 18847;i++)
	{
		DataIndex[i] = 0;
	}
	for (int i = 0; i < OBJ_NUM; i ++)
	{
		m_parallel3DObj[i].pColors = new CVector3[VertexNum[i]];
	}
	for (int i = 0; i < OBJ_NUM; i++)
	{
		for (int j = 0; j < VertexNum[i]; j++)
		{
			m_parallel3DObj[i].pColors[j].x = 255;
			m_parallel3DObj[i].pColors[j].y = 255;
			m_parallel3DObj[i].pColors[j].z = 255;
		}
	}
	this->start();
}

void DataAdapter::run()
{
	ofstream ofile;
	ofile.open("log.txt");
	bool StartLoop = true;
	DoRead = true;
	char one = '1';
	int SpikedNum = 0;
	while (StartLoop)
	{
	//	sleep(100);
		while (DoRead)
		{
			if (m_OriginalData.do_Facade_Data())
			{
				m_FrameList = m_OriginalData.m_FrameList;
				// rendering process
				for (int k = 0; k < m_FrameList.size(); k++)
				{
					for (int i = 0; i < m_FrameList[k].neuro_data.size(); i++)
					{
						string Str_bit40 = m_FrameList[k].neuro_data[i].to_string();
						for (int j = 0; j < Str_bit40.length(); j++)
						{
							

							int Index = ((i * 40) + j)*18847/(40*256);
							
							if (Str_bit40[j] == one)
							{
// 								ofile << "Str_bit40: " << i << endl;
// 								ofile << "Str_bit40: " << j << endl;
								ofile <<"Index: " <<Index << endl;
								DataIndex[Index] = 1;//could be transfered by address code
								SpikedNum++;
							}
							else
							{
								DataIndex[Index] = 0;
							}
						}
					}
				}
				ofile << "SpikedNum: " << SpikedNum << endl;
				SpikedNum = 0;
				for (int i = 0; i < OBJ_NUM; i ++)
				{
					for (int j = 0; j < VertexNum[i]; j ++)
					{
						m_parallel3DObj[i].pColors[j].x = i % 255;
						m_parallel3DObj[i].pColors[j].y = j % 255;
						m_parallel3DObj[i].pColors[j].z = (i + j) % 255;
					}
				}
				m_OriginalData.m_FrameList.clear();
			}
			else
			{
				StartLoop = false;
			}
			DoRead = false;
		}
	}
}

