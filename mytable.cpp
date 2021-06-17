#include <QtGui>
#include "mytable.h"
#include <QRegExp>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QTableWidgetItem>
#include <QDebug>
#include <QTextStream>
#include<fstream>
using namespace std;

mytable::mytable(QWidget *parent, ifstream* in ) : QTableWidget(parent)
{
	this->names={};
     table = new QTableWidget();
     QHBoxLayout *layout = new QHBoxLayout;

     layout->addWidget(table);
     setLayout(layout);

    string url0 = "https://api.coingecko.com/api/v3/coins/list";

    read = new MyDataReader(url0, *in);

    connect(read, &MyDataReader::done, this, &mytable::dothings);
    //bool success = connect(read, SIGNAL(done(vector<string>*)), this, SLOT(dothings(vector<string>*)));
    //Q_ASSERT(success);
     /*manager = new QNetworkAccessManager(this) ; 

     connect(manager, SIGNAL(finished(QNetworkReply *)),this, SLOT(replyFinished(QNetworkReply *)));

     std::string url = "https://api.coingecko.com/api/v3/simple/price?ids=" + this->names[0];
     for(unsigned int i = 1; i<this->names.size(); i++){
     	url += "," + this->names[i];
     }
     url += "&vs_currencies=usd,eur,gbp";

     QString qurl = QString::fromStdString(url);
     manager->get(QNetworkRequest(QUrl(qurl)));*/
}

void mytable::dothings(vector<string>* ids) {
    cout << "Im gonna do this rn" << endl;
    this->names = *ids;
    for(auto a: this->names){
            cout << a << endl;
        }
    manager = new QNetworkAccessManager(this) ; 

    connect(manager, SIGNAL(finished(QNetworkReply *)),this, SLOT(replyFinished(QNetworkReply *)));

    std::string url = "https://api.coingecko.com/api/v3/simple/price?ids=" + this->names[0];
     for(unsigned int i = 1; i<this->names.size(); i++){
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

	for(unsigned int i=0; i<this->names.size(); i++){

		QString usd, eur, gbp; 
    	int pos = 0;
    	
    	std::string pat = "\"" + this->names[i] + "\":\\{\"usd\":(\\d+\\.?\\d+),\"eur\":(\\d+\\.?\\d+),\"gbp\":(\\d+\\.?\\d+)";
    	QString pattern = QString::fromStdString(pat);
     	QRegExp rx(pattern);

	 	if ( rx.indexIn(data, pos) != -1 ) {
	       usd =  rx.cap(1);    // rate found 
	       eur =  rx.cap(2);
	       gbp =  rx.cap(3);
	    } else {
	       usd = QString("Error"); 
	       eur = QString("Error"); 
	       gbp = QString("Error"); 
	    }

	    table->insertRow(table->rowCount());
	    table->setItem(table->rowCount()-1, 0, new QTableWidgetItem(QString::fromStdString(this->names[i])));
		table->setItem(table->rowCount()-1, 1, new QTableWidgetItem(usd));
		table->setItem(table->rowCount()-1, 2, new QTableWidgetItem(eur));
		table->setItem(table->rowCount()-1, 3, new QTableWidgetItem(gbp));
	}
    
}