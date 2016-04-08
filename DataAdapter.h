#pragma once
#include "OriginalData.h"
#include <QTimer>
#include <QThread>
#include "MAIN.H"
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
	int CurrentFrameIndex;
private:
	int ReadStep;
	bool DoRead;
	QtDirObserver m_DirObserver;

};