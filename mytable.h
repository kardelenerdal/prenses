#include <QtGui>
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
      void replyFinished(QNetworkReply * reply) ; 

    private:
      QTableWidget *table;
      QNetworkAccessManager *manager;

} ;
