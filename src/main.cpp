
#include <QApplication>

#include "qbizmanager.h"
#include <QtCore>
#include <QTextCodec>
#include <QDebug>

#include <QObject>

#include <QtDebug>
#include <QFile>
#include <QTextStream >
void customMessageHandler(QtMsgType type, const char *msg)
{
    QString txt;
    switch (type)
   {
    case QtDebugMsg:     //调试信息提示
            txt = QString("%1 Debug: %2\r\n").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(msg);
            break;
    case QtWarningMsg:  //一般的warning提示
            txt = QString("%1 Warning: %2\r\n").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(msg);
            break;
    case QtCriticalMsg:    //严重错误提示
            txt = QString("Critical: %1\r\n").arg(msg);
            break;
    case QtFatalMsg:      //致命错误提示
            txt = QString("Fatal: %1\r\n").arg(msg);
            abort();
   default:
           break;
    }

    QFile outFile(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh")+".txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    qInstallMsgHandler(customMessageHandler);


	QBizManager b;
    b.todo();
    return a.exec();
}

