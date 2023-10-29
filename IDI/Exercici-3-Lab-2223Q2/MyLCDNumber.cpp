#include "MyLCDNumber.h"

MyLCDNumber::MyLCDNumber(QWidget *parent=0):QLCDNumber(parent)
{
	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &MyLCDNumber::showTime);
	tRecord = QTime::fromString("00:00:00:000","hh:mm:ss:zzz");
	tChrono = QTime::fromString("00:00:00:000","hh:mm:ss:zzz");
	firstTry = true;
	restart();
	timer->start(1);
}

MyLCDNumber::~MyLCDNumber()
{
}

void MyLCDNumber::storeRecord(){
	if(tRecord.msecsTo(tChrono) < 0 or (firstTry and tChrono != QTime::fromString("00:00:00:000","hh:mm:ss:zzz")))
	{
		if (firstTry) firstTry = 0;
		tRecord = tChrono;
		emit printRecord("Rècord: " + tRecord.toString("hh:mm:ss:zzz"));
	}
}

void MyLCDNumber::restart()
{
	storeRecord();
	tChrono = QTime::fromString("00:00:00:000","hh:mm:ss:zzz");
	emit chronoColor("color: rgb(0, 0, 0)");
	started = false;
}

void MyLCDNumber::start_stop()
{
	tIniChrono = QTime::currentTime();
	started = not started;
}

void MyLCDNumber::showTime()
{
	if(tChrono == tRecord or firstTry or tChrono == QTime::fromString("00:00:00:000","hh:mm:ss:zzz")) emit chronoColor("color: rgb(0, 0, 0)");
	else if (tChrono < tRecord) emit chronoColor("color: rgb(0, 210, 0)");
	else emit chronoColor("color: rgb(210, 0, 0)");
	if(started) tChrono = tChrono.addMSecs(tIniChrono.msecsTo(QTime::currentTime()));
	tIniChrono = QTime::currentTime();
    QString text = tChrono.toString("hh:mm:ss:zzz");
    display(text);
}
