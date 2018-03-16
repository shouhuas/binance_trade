#ifndef QBIZMANAGER_H
#define QBIZMANAGER_H
#include <QObject>
#include "qhttpmanager.h"
#include <QTimer>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMap>
#include <QHash>
#include <QSet>



class QBizManager : public QObject
{
 Q_OBJECT
public:
    QBizManager( );

     ~QBizManager();
public:
     bool initDb();
	 double GetBalance();
	 void order(const double& rate, const QString & buysell, const double & amount, const QString & sys);
	 double price(const QString & ssymbol);

	 void todo();

	 void CancelTrade(const QString & OrderId);
private:

	QString publicKey ;
	QString secret ;

};



#endif // QBIZMANAGER_H
