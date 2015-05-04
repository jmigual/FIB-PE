#ifndef MAINCLASS
#define MAINCLASS

#include <QByteArray>
#include <QDebug>
#include <QJsonDocument>
#include <QObject>
#include <QtNetwork>
#include <QTimer>

#include <iostream>
using namespace std;

class MainClass : QObject
{
    Q_OBJECT
    
public:
    
    /// Default constructor
    MainClass(int argc, char *argv[]);
    
    /// Default destructor
    ~MainClass();
    
signals:
    void downloaded(QString);
    
private:
    
    /// Network controler
    QNetworkAccessManager *_acc;
    
    /// Contains the PC information data
    QJsonObject _dataPC;

    /// Contains the file path to the downloaded data
    QString _fileD;

    /// Contains the file path to write the data
    QString _fileW;
    
    /// To view if an error occurred
    QNetworkReply *_rep;
    
    /// Contains the network request
    QNetworkRequest _req;
    
    /// Time to sleep
    static const unsigned int _time = 6*1000; // 6 s
    
    /// Contains the url
    const QString _url = "https://raco.fib.upc.edu/api/aules/places-lliures.json";
    
    void lectura();
    
private slots:
    void timerEvent(QTimerEvent *);
    
    void downloaded(QNetworkReply *rep);
    
    void error(QNetworkReply::NetworkError code);
    
};

#endif // MAINCLASS
