#include<iostream>
#include<fstream>
#include<vector>
#include <QtCore>
#include <QApplication>
#include <QTableWidget>
#include "mytable.h"

int main(int argc, char *argv[]) {
	
	/**path = getenv ("MYCRYPTOCONVERT");
	ifstream infile;  
	infile.open(path);
	string name;
	vector<string> names;
	while(infile >> name){
		names.push_back(name);
	}**/

	
	QApplication a(argc, argv); 
   	mytable my; 

   	my.show(); 

   	return a.exec();
	
}