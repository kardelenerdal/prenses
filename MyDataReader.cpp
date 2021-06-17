#include <QtGui>
#include "MyDataReader.h"
#include <QRegExp>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <iostream>
#include<fstream>

using namespace std;

MyDataReader::MyDataReader(string url, ifstream& infile){

	this->in = &infile;
	 
	manager = new QNetworkAccessManager(this) ; 


    connect(manager, SIGNAL(finished(QNetworkReply *)),this, SLOT(replyFinished(QNetworkReply *)));

    QString qurl = QString::fromStdString(url);
    
    cout << "hello2" << endl;
    manager->get(QNetworkRequest(QUrl(qurl)));

}

void MyDataReader::replyFinished(QNetworkReply *reply)  {
		cout << "hello" << endl;
    	QString data = (QString) reply->readAll();
    	string token; 
    	std::vector<std::string> ids {"bitcoin","ethereum","ripple","litecoin","monero","zcash"};

    	while((this->in)->peek() != EOF) {

			getline(*(this->in), token);
			cout << token<< endl;
			string pat = "([a-zA-Z\\-\\d]+)\",\"symbol\":\"" + token +"\"";
			QString pattern = QString::fromStdString(pat);
			qDebug() << pattern;
			QRegExp rx(pattern);

			int pos = 0;
			if(rx.indexIn(data, pos) != -1){
				cout << "hello1"<< endl;
				ids.push_back(rx.cap(1).toStdString());
				continue;
			}
			string pat2 = "([a-zA-Z\\-\\d]+)\",\"symbol\":\"([a-zA-Z\\-\\d\\s]+)\",\"name\":\"" + token + "\"";
			QString pattern2 = QString::fromStdString(pat2);
			QRegExp rx2(pattern2);
			if(rx2.indexIn(data, pos) != -1){
				cout << "hello2"<< endl;
				ids.push_back(rx2.cap(1).toStdString());
			}
		
		}

		for(auto a: ids){
			cout << a << endl;
		}

		emit done(&ids);

}