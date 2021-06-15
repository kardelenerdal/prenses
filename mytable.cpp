#include <QtGui>
#include "mytable.h"
#include <QRegExp>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QTableWidgetItem>

mytable::mytable(QWidget *parent) : QTableWidget(parent)
{

     table = new QTableWidget();
     QHBoxLayout *layout = new QHBoxLayout;

     layout->addWidget(table);
     setLayout(layout);

     manager = new QNetworkAccessManager(this) ; 

     connect(manager, SIGNAL(finished(QNetworkReply *)),this, SLOT(replyFinished(QNetworkReply *)));

     // Initiate retrieval of  the data from the web page.
     // When completed, slot replyFinished will be called. 
     manager->get(QNetworkRequest(QUrl("https://www.bitstamp.net/api/v2/ticker/btcusd")));
}


void mytable::replyFinished(QNetworkReply *reply)  {

     QString str ; 
     int pos = 0;

     // read the data fetched from the web site 
     QString data = (QString) reply->readAll();

     // use pattern matching to extract the rate 
     QRegExp rx("\"last\": \"(\\d+\\.\\d+)\"");

 	if ( rx.indexIn(data, pos) != -1 ) {
       str = QString("BTC/USD:  ") + rx.cap(1);    // rate found 
     }
     else {
       str = QString("Error") ; 
     }

     table->setRowCount(2);
     table->setColumnCount(1);
     QTableWidgetItem *newItem = new QTableWidgetItem();
     newItem->setText(str);
     table->setItem(0, 0, newItem);
}