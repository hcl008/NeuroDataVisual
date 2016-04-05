#include "QtDirObserver.h"

QtDirObserver::QtDirObserver()
{
	this->start();
	CurrentCursor = 0;
	
}

void QtDirObserver::run()
{


	FilePath = "C:\\Data";
	while (1)
	{
		QDir * m_pDir = new QDir(FilePath);
		QStringList filter;
		filter << "spk_recorded*";
		m_pDir->setNameFilters(filter);
		QList<QFileInfo> *fileInfo = new QList<QFileInfo>(m_pDir->entryInfoList(filter));
		fileInfo->count();
		CurrentCursor = fileInfo->size();
		delete m_pDir;
		delete fileInfo;
	}

}

