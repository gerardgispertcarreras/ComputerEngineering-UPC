#include <QLCDNumber>
#include <QTimer>
#include <QTime>
#include <QDebug>

class MyLCDNumber:public QLCDNumber
{
	Q_OBJECT
	public:
		MyLCDNumber(QWidget *parent);
		~MyLCDNumber();
	private:
		QTime tIniChrono, tChrono, tRecord;
		bool started, firstTry;
	public slots:
		void showTime();
		void start_stop();
		void restart();
		void storeRecord();

	signals:
		void printRecord(QString str);
		void chronoColor(QString str);
};