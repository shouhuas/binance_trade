#include "qbizmanager.h"
#include "qhttpmanager.h"
#include <queue>
#include <QObject>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <QVariant>

using namespace std;

QBizManager::QBizManager( )
{
	publicKey = "vmPUZE6mv9SD5VNHk4HlWFsOr6aKE2zvsw0MuIgwCIPy6utIco14y7Ju91duEh8A";
	secret = "NhqPtmdSJYdKjVHjA7PZj4Mge3R5YNiP1e3UZjInClVN65XAbvqqM6A7H5fATj0j";
    initDb();

}


//! [0]
bool QBizManager::initDb()
{
    QSqlDatabase  db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("a.db");
    if (!db.open()) {

        return false;
    }

  
    return true;
}


QBizManager::~QBizManager()
{
}


void QBizManager::order(const double & rate, const QString & buysell, const double & amount, const QString & sys)
{
	QString currentMSecsSinceEpoch = QString("%1").arg(QDateTime::currentMSecsSinceEpoch());
	QString timestamp = currentMSecsSinceEpoch;

	QString url = "https://api.binance.com/api/v3/order";
	QString queryString = "symbol="+ sys +"&side="+ buysell +"&type=LIMIT&timeInForce=GTC&quantity="+QString::number(amount,  'f', 2) +"&price=" + QString::number(rate ,'f', 5) + "&recvWindow=5000&timestamp=" + timestamp;
	QString signature = QMessageAuthenticationCode::hash(queryString.toLatin1(), secret.toLatin1(), QCryptographicHash::Sha256).toHex();
	
	QString post_data = queryString + "&signature=" + signature;

	QByteArray send;
	send.append(post_data);
	QString source;
	QHttpManager::GetInstance().HttpPost("https://api.binance.com/api/v3/order", send, source, publicKey);
}



void QBizManager::CancelTrade(const QString & OrderId)
{
	QString currentMSecsSinceEpoch = QString("%1").arg(QDateTime::currentMSecsSinceEpoch());
	QString timestamp = currentMSecsSinceEpoch;

	QString url = "https://api.binance.com/api/v3/order";
	QString queryString = "symbol=LTCBTC&side=BUY&type=LIMIT&timeInForce=GTC&quantity=1&price=0.0021&recvWindow=5000&timestamp=" + timestamp;
	QString signature = QMessageAuthenticationCode::hash(queryString.toLatin1(), secret.toLatin1(), QCryptographicHash::Sha256).toHex();

	QString post_data = queryString + "&signature=" + signature;

	QByteArray send;
	send.append(post_data);
	QString source;
	QHttpManager::GetInstance().HttpPost("https://api.binance.com/api/v3/order", send, source, publicKey);
}

double QBizManager::GetBalance()
{	
	QString currentMSecsSinceEpoch = QString("%1").arg(QDateTime::currentMSecsSinceEpoch());
	QString timestamp = currentMSecsSinceEpoch;


	QString queryString = "recvWindow=5000&timestamp=" + timestamp;
	QString signature = QMessageAuthenticationCode::hash(queryString.toLatin1(), secret.toLatin1(), QCryptographicHash::Sha256).toHex();

	QString post_data = queryString + "&signature=" + signature;

	QByteArray send;
	send.append(post_data);
	QString source;
	
	QString url = "https://api.binance.com/api/v3/account?" + post_data;
	QHttpManager::GetInstance().HttpGet_binance(url, publicKey,source);

	int p = source.indexOf("BTC\",\"free");
	int p1 = source.indexOf("\"",p+15);
	QString btc = source.mid(p + 13, p1-p-13);
	return btc.toDouble();
}

double QBizManager::price(const QString & symbol)
{
	QString url = "https://api.binance.com/api/v3/ticker/price?symbol="+ symbol;
	QString source;
	QHttpManager::GetInstance().HttpGet(url, source);

	int p = source.indexOf("price");
	QString price = source.mid(p + 8, 10);
	return price.toDouble();
}


void QBizManager::todo()
{

	double btc_balance = GetBalance();
	double rate;
	int buysell;
	double  amount;
    QString  symbol ="LTCBTC";

	double b_price = price(symbol);

	//1 分钟出现暴跌90% 全仓买入
	while (true)
	{
		double cur_price = price(symbol);


		if (cur_price < b_price * 0.20) //出现1分钟出现暴跌90% 机会
		{
			//按照当前价格1.1倍买入
			double buy_rate = cur_price * 1.1;

			double btc_balance = GetBalance();

			double amount = btc_balance *0.95 / buy_rate;

			order(buy_rate, "BUY", amount, symbol);
		}
		b_price = cur_price;

		//一分钟
		QTimer   timer;
		timer.setSingleShot(true);
		QEventLoop loop;
		connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
		timer.start(1000 * 10);
		loop.exec();
	}
}