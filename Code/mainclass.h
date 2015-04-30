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
    MainClass();
    
    /// Default destructor
    ~MainClass();
    
    /// Main loop
    void start();
    
signals:
    void downloaded(QString);
    
private:
    
    /// Network controler
    QNetworkAccessManager *_acc;
    
    /// To view if an error occurred
    QNetworkReply *_rep;
    
    /// Contains the network request
    QNetworkRequest _req;
    
    /// Time to sleep
    static const unsigned int _time = 60*15;
    
    /// Contains the url
    const QString _url = "https://raco.fib.upc.edu/api/aules/places-lliures.json";
    
    void lectura();
    
private slots:
    void download();
    
    void downloaded(QNetworkReply *rep);
    
    void error(QNetworkReply::NetworkError code);
    
};

#endif // MAINCLASS
