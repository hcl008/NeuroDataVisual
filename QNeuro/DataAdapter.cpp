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

int DataAdapter::SpikedNum = 0;

DataAdapter::DataAdapter()
{
	m_parallel3DObj = new t3DParallelColor[OBJ_NUM];
	DataIndex = new int[18847];//18847 = total point number in brain obj
	AddressCode = new V3D[40]; //40 == neuro address count
	for (int i = 0; i < 40; i++)
	{
		AddressCode[i].R = ((float)((rand() % 255))) / 255;
		AddressCode[i].G = ((float)((rand() % 255))) / 255;
		AddressCode[i].B = ((float)((rand() % 255))) / 255;
	}
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
//reserved this function for further rendering
void DataAdapter::GenerateAddressCode(string Str_bit19, int Index)
{
	
	for (int i = 0; i < Str_bit19.length(); i++)
	{
		bitset<8> temp_bit8_R(Str_bit19.substr(0, 7));
		bitset<8> temp_bit8_G(Str_bit19.substr(7, 6));
		bitset<8> temp_bit8_B(Str_bit19.substr(13, 6));
		temp_bit8_R << 1;
		temp_bit8_G << 2;
		temp_bit8_B << 2;
		AddressCode[Index].R = (float)((float)(temp_bit8_R.to_ulong()) / 255);
		AddressCode[Index].G = (float)((float)(temp_bit8_G.to_ulong()) / 255);
		AddressCode[Index].B = (float)((float)(temp_bit8_B.to_ulong()) / 255);

	}

}

int DataAdapter::CurrentFrameIndex = 0;

void DataAdapter::run()
{
	ofstream ofile;
	
	bool StartLoop = true;
	DoRead = true;
	char one = '1';
	int IndexCusor = 0;
	CurrentFrameIndex = 0;
	ofile.open("log.txt");
	int RandPosition;
	int RandFrame;
	while (1)
	{
	//	sleep(100);
		while (DoRead)
		{
			RandFrame = (rand() % 100);
			if (RandFrame < 15)
			{
				IndexCusor = (rand() % 18848);
			}
			if (m_DirObserver.CurrentCursor-1 > 2)
			{
				if (m_OriginalData.do_Facade_Data(CurrentFrameIndex))
				{
					m_FrameList = m_OriginalData.m_FrameList;
					// rendering process
					for (int k = 0; k < m_FrameList.size(); k++)
					{
						// 					for (int i = 0; i < m_FrameList[k].neuro_address.size(); i++)
						// 					{
						// 						string Str_bit19 = m_FrameList[k].neuro_address[i].to_string();
						// 						GenerateAddressCode(Str_bit19, i);
						// 					}
						// 					

						std::bitset<128> bit_128;
						bit_128.reset();
						int LoopCursor = 0;

						memset(DataIndex, 0, 18848*4);
						
						//mingqi modify
						for (int i = 0; i < m_FrameList[k].neuro_data.size(); i++)
						{

					//		string Str_bit40 = m_FrameList[k].neuro_data[i].to_string();
							for (int j = 0; j < m_FrameList[k].neuro_data[i].size(); j++)
							{

								

//								int Index = ((j * 256) + i) * 18847 / (40 * 256);
								int Index = (IndexCusor + LoopCursor) % 18847;
								if (m_FrameList[k].neuro_data[i][j])
								{
									if (j == AdditionalInfo::EngineIndex)
									{
										bit_128.set(i / 2); //map 256 -> 128
									}



									if (AdditionalInfo::NeuroEngineMartix.size()>0)
									{
										AdditionalInfo::NeuroEngineMartix[j] = true;//NEW
									}
									
									// 								ofile << "Str_bit40: " << i << endl;
									// 								ofile << "Str_bit40: " << j << endl;
									LoopCursor++;
									LoopCursor++;
									IndexCusor++;
									
//									ofile << "Index: " << Index << endl;
//									ofile.close();
									DataIndex[Index] = j;//could be transfered by address code
									SpikedNum++;
								}
								else
								{
									if (AdditionalInfo::NeuroEngineMartix.size() > 0)
									{
										AdditionalInfo::NeuroEngineMartix[j] = false;//NEW
									}
							//		DataIndex[Index] = 0;
								}
							}
						}
						AdditionalInfo::RasterPlot.push_back(bit_128);
					}
					AdditionalInfo::UpdateNCPF(); //update addition info here



// 					ofile.open("log.txt");
// 					ofile << "SpikedNum: " << SpikedNum << endl;
// 					ofile.close();
					SpikedNum = 0;
					for (int i = 0; i < OBJ_NUM; i++)
					{
						for (int j = 0; j < VertexNum[i]; j++)
						{
							m_parallel3DObj[i].pColors[j].x = i % 255;
							m_parallel3DObj[i].pColors[j].y = j % 255;
							m_parallel3DObj[i].pColors[j].z = (i + j) % 255;
						}
					}
					m_OriginalData.m_FrameList.clear();
					CurrentFrameIndex++;
				}

				
				DoRead = false;
			}
			else
			{
		//		sleep(300);
			}
		}//(m_DirObserver.CurrentCursor-1 > CurrentFrameIndex)
	}
}



