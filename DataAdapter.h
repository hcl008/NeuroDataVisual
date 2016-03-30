#pragma once
#include "OriginalData.h"
#include <QTimer>
#include <QThread>
#include "MAIN.H"
#define OBJ_NUM 8


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
	int * DataIndex;
private:
	int ReadStep;
	bool DoRead;


};