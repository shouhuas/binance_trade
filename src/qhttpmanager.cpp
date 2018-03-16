#include "qhttpmanager.h"
#include <QObject>
QHttpManager::QHttpManager( QObject *parent) :
    QObject(parent)
{
}

bool QHttpManager::HttpGet(const QString& url,QString& web)
 {
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request;
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1);
    request.setSslConfiguration(config);

    request.setUrl(QUrl(url));
    request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
    request.setRawHeader("Accept-Language", "zh-CN,zh;q=0.8,en;q=0.6");
    QNetworkReply *reply =    manager->get(request);

    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;

    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray responseData;
    responseData =  reply->readAll();
    web = QString(responseData);
    reply->close();
    reply->abort();

    delete manager;

    return true;
 }

bool QHttpManager::HttpPost(const QString &url,const QByteArray &send,QString& web,QString sign)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request;
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1);
    request.setSslConfiguration(config);


    request.setUrl(QUrl(url));
    QString  ContentTypeHeader = "application/json";
    request.setHeader(QNetworkRequest::ContentTypeHeader,ContentTypeHeader);
    request.setHeader(QNetworkRequest::ContentLengthHeader,send.length());
	request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
	request.setRawHeader("Accept-Language", "zh-CN,zh;q=0.8,en;q=0.6");
	request.setRawHeader("X-MBX-APIKEY", sign.toAscii());
    QNetworkReply *reply = manager->post(request,send);

    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;

    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray responseData;
    responseData =  reply->readAll();
    web = QString(responseData);
    reply->close();
    reply->abort();
    manager->deleteResource(request);
    manager->deleteLater();
    delete manager;

    return true;
}


bool QHttpManager::HttpGet_binance(const QString& url, const QString& APIkey,QString& web)
{
	QNetworkAccessManager* manager = new QNetworkAccessManager();
	QNetworkRequest request;
	QSslConfiguration config;
	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	config.setProtocol(QSsl::TlsV1);
	request.setSslConfiguration(config);

	request.setUrl(QUrl(url));
	request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
	request.setRawHeader("Accept-Language", "zh-CN,zh;q=0.8,en;q=0.6");

	request.setRawHeader("X-MBX-APIKEY", APIkey.toAscii());
	QNetworkReply *reply = manager->get(request);

	QTimer timer;
	timer.setSingleShot(true);
	QEventLoop loop;

	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	QByteArray responseData;
	responseData = reply->readAll();
	web = QString(responseData);
	reply->close();
	reply->abort();

	delete manager;

	return true;
}

bool QHttpManager::huobi_HttpPost(const QString &url,const QByteArray &send,const QByteArray &authToken,QString tonce,QString& web)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request;
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1);
    request.setSslConfiguration(config);


    request.setUrl(QUrl(url));
    QString  ContentTypeHeader = "application/json-rpc";
    request.setHeader(QNetworkRequest::ContentTypeHeader,ContentTypeHeader);
    request.setHeader(QNetworkRequest::ContentLengthHeader,send.length());

    request.setRawHeader("Accept", "application/json, text/javascript, */*; q=0.01");

    request.setRawHeader("Authorization", "Basic " + authToken);
    request.setRawHeader("Json-Rpc-Tonce", tonce.toAscii());
    request.setRawHeader("Accept-Language", "zh-CN,zh;q=0.8,en;q=0.6");

    QNetworkReply* reply = manager->post(request,send);

    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;

    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray responseData;
    responseData =  reply->readAll();
    web = QString(responseData);
    reply->close();
    reply->abort();

    delete manager;
    return true;
}
bool QHttpManager::onFinished(QString& web)
{
//    if (reply->error() == QNetworkReply::NoError) {
//        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
//        switch (statusCode) {
//            case 301:
//            case 302:
//            case 307:
//                   {
//                    QString redirect = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl().toString();
//                    if(redirect.indexOf("http://")==-1)
//                    {
//                        QString tmp= "http://www.beyond.com";
//                        tmp += redirect;
//                        redirect = tmp;
//                    }
//                    HttpGet(redirect,web);
//        }
//            break;

//            case 200:
//                QByteArray responseData;
//                responseData =  reply->readAll();
//                web = QString(responseData);
//                reply->close();
//                break;
//        }
//    }else if(reply->error()==QNetworkReply::UnknownNetworkError)
//    {
//        int e = reply->error();
//         //murl ="net e";
//    }else  if(reply->error()==QNetworkReply::ServiceUnavailableError)
//    {
//        int e = reply->error();
//        // murl ="dd";
//    }else
//    {
//        int e = reply->error();
//    }
	return 0;
}
