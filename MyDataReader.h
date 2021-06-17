#include <QtGui>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <iostream>
#include <fstream>
using namespace std;

class MyDataReader : public QObject
{
    Q_OBJECT

    public:
      MyDataReader(string url, ifstream& in);
      ifstream* in;
	 
	signals:
		void done(vector<string>* ids);

    public slots:
      void replyFinished(QNetworkReply * reply) ; 

    private:
      QNetworkAccessManager *manager;

} ;