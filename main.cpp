#include<iostream>
#include<fstream>
#include<vector>
#include <QtCore>
#include <QApplication>
#include <QTableWidget>
#include <QtGui>
#include "mytable.h"
#include <QDebug>

using namespace std;

int main(int argc, char *argv[]) {
	

	//export MYCRYPTOCONVERT=/home/cmpe250student/Desktop/prenses-main/test.txt

	//string path = getenv ("MYCRYPTOCONVERT");
	ifstream infile;  
	infile.open("test.txt");
	string name;
	//vector<string> ids;


	//std::vector<std::string> ids {"bitcoin","ethereum","ripple","litecoin","monero","zcash"};
	string url = "https://api.coingecko.com/api/v3/coins/list";

	QApplication a(argc, argv);

	//MyDataReader read(url, infile);

	mytable my(0, &infile);
	
	my.show(); 


	cout << "hey" << endl;
	//qDebug() << read.data;
	cout << "lol" << endl;


   	return a.exec();
	
}