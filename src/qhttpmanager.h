#ifndef QHTTPMANAGER_H
#define QHTTPMANAGER_H
#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>

class QHttpManager  : public QObject
{
    Q_OBJECT
public:
    QHttpManager( QObject *parent = 0);
public:
    static   QHttpManager&							GetInstance(){static QHttpManager cbm;return cbm;}

    bool HttpPost(const QString &url,const QByteArray &send,QString& web,QString sign=0);
    bool HttpGet(const QString& url,QString& web);
	bool HttpGet_binance(const QString& url, const QString& APIkey, QString& web);
	bool huobi_HttpPost(const QString &url,const QByteArray &send,const QByteArray &authToken,QString tonce,QString& web);


private:


        bool onFinished(QString& web);

//QNetworkAccessManager* manager;

    QUrl m_url;
};

#endif // QHTTPMANAGER_H
