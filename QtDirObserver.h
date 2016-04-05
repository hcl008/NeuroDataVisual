#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QThread>
#include <QList>
#include <list>
#include <fstream>
using namespace std;
class QtDirObserver:public QThread
{

public:
	QtDirObserver();
	~QtDirObserver(){};
	void run();
	int CurrentCursor;
private:


	QString FilePath;
	static QString FilePreName;




};