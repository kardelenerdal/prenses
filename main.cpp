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

	std::vector<std::string> names {"Bitcoin","Ethereum","Ripple","Litecoin","Monero","Zcash"};
	// sembollerden name'i alicaz
	QApplication a(argc, argv); 
   	mytable my(0, names);

   	my.show(); 

   	return a.exec();
	
}