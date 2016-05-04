#pragma once
#include "OriginalData.h"
#include <QTimer>
#include <QThread>
#include "MAIN.H"
#include "AdditionalInfo.h"//NEW
#define OBJ_NUM 8
struct V3D
{
	float R;
	float G;
	float B;
};

class DataAdapter:QThread
{
	
	Q_OBJECT

public:
	static int SpikedNum;//NEW
	static int CurrentFrameIndex;//NEW


	DataAdapter();
	~DataAdapter(){};
	void run();
	GetDataProcess m_OriginalData;
	int GetReadStep()
	{
		return ReadStep;
	}
	bool GetDoRead()
	{
		return DoRead;
	}
	void SetDoRead(bool mDoRead)
	{
		this->DoRead = mDoRead;
	}
	vector<Frame> m_FrameList;
	t3DParallelColor * m_parallel3DObj;
	void GenerateAddressCode(string Str_bit19,int Index);
	int * DataIndex;
	V3D * AddressCode;
<<<<<<< HEAD:QNeuro/DataAdapter.h
	
=======
	int CurrentFrameIndex;
>>>>>>> 20c52743ecfcbbe87dc1495bdf86c54c3d2379d7:DataAdapter.h
private:
	int ReadStep;
	bool DoRead;
	QtDirObserver m_DirObserver;

};