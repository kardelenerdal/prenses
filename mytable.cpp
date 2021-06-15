#include <QtGui>
#include "mytable.h"
#include <QRegExp>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QTableWidgetItem>

mytable::mytable(QWidget *parent, std::vector<std::string> names) : QTableWidget(parent)
{
	this->names = names;
     table = new QTableWidget();
     QHBoxLayout *layout = new QHBoxLayout;

     layout->addWidget(table);
     setLayout(layout);

     manager = new QNetworkAccessManager(this) ; 

     connect(manager, SIGNAL(finished(QNetworkReply *)),this, SLOT(replyFinished(QNetworkReply *)));

     // Initiate retrieval of  the data from the web page.
     // When completed, slot replyFinished will be called. 
     // https://api.coingecko.com/api/v3/simple/price?ids=bitcoin,litecoin,ethereum&vs_currencies=usd,eur,gbp
     std::string url = "https://api.coingecko.com/api/v3/simple/price?ids=" + this->names[0];
     for(int i = 1; i<this->names.size(); i++){
     	url += "," + this->names[i];
     }
     url += "&vs_currencies=usd,eur,gbp";
     QString qurl = QString::fromStdString(url);
     manager->get(QNetworkRequest(QUrl(qurl)));
}


void mytable::replyFinished(QNetworkReply *reply)  {

	// read the data fetched from the web site 
    QString data = (QString) reply->readAll();
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels(QStringList() << tr("") <<tr("USD") << tr("EUR") << tr("GBP"));

	for(int i=0; i<this->names.size(); i++){

		QString usd, eur, gbp; 
    	int pos = 0;
    	// "litecoin":{"usd":176.3,"eur":145.37,"gbp":125.17}
    	std::string pat = "\"" + this->names[i] + "\":{\"usd\":(\\d+\\.\\d+),\"eur\":(\\d+\\.\\d+),\"gbp\":(\\d+\\.\\d+)}";
    	QString pattern = QString::fromStdString(pat);
    	// use pattern matching to extract the rate 
     	QRegExp rx(pattern);

	 	if ( rx.indexIn(data, pos) != -1 ) {
	       usd =  rx.cap(1);    // rate found 
	       eur =  rx.cap(2);
	       gbp =  rx.cap(3);
	    }
	    else {
	       usd = QString("Error") ; 
	       eur = QString("Error") ; 
	       gbp = QString("Error") ; 
	    }

	    table->insertRow(table->rowCount());
	    table->setItem(table->rowCount()-1, 0, new QTableWidgetItem(QString::fromStdString(names[i])));
		table->setItem(table->rowCount()-1, 1, new QTableWidgetItem(usd));
		table->setItem(table->rowCount()-1, 2, new QTableWidgetItem(eur));
		table->setItem(table->rowCount()-1, 3, new QTableWidgetItem(gbp));
	}
    
}