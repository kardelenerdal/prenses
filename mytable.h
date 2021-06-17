#include <QtGui>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTableWidget>
#include <vector>
#include <fstream>
#include "MyDataReader.h"

class mytable : public QTableWidget
{
    Q_OBJECT

    public:
      mytable(QWidget *parent = 0, std::ifstream* in = nullptr);
      std::vector<std::string> names;
   
   
    public slots:
      void dothings(std::vector<std::string>* ids);
      void replyFinished(QNetworkReply * reply) ; 

    private:
      QTableWidget *table;
      QNetworkAccessManager *manager;
      MyDataReader *read;
} ;



/*#include <QtGui>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTableWidget>
#include <vector>

class mytable : public QTableWidget
{
    Q_OBJECT

    public:
      mytable(QWidget *parent = 0, std::vector<std::string> names = {});
      std::vector<std::string> names;
	 
	 
    public slots:
      void dothings();
      void replyFinished(QNetworkReply * reply) ; 

    private:
      QTableWidget *table;
      QNetworkAccessManager *manager;

} ;*/
