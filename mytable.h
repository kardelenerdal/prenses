#include <QtGui>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTableWidget>

class mytable : public QTableWidget
{
    Q_OBJECT

    public:
      mytable(QWidget *parent = 0);
	 
	 
    public slots:
      void replyFinished(QNetworkReply * reply) ; 

    private:
      QTableWidget *table;
      QNetworkAccessManager *manager;
} ;
