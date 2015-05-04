#ifndef MAINCLASS
#define MAINCLASS

#include <QByteArray>
#include <QDebug>
#include <QHash>
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
    
    /// Contains the current timetable of the class
    QHash< QString, QVector<bool> > _classe;
    
    /// Contains the name of the classrooms
    QVector< QString > _className = { "A5S102", "A5S103", "A5S104", "A5S105",
                                      "A5S108", "A5S109", "A5S111", "A5S112", 
                                      "A5S113", "B5S101", "B5S201", "B5S202", 
                                      "C6S301", "C6S302", "C6S303", "C6S304", 
                                      "C6S306", "C6S308", "C6S309" };
    
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
    static const unsigned int _time = 6000;
    
    /// Timer for every day update
    QTimer _timer;
    
    /// Time to sleep every day
    static const unsigned int _timeD = 24*3600*1000;
    
    /// Contains the url
    const QString _url = "https://raco.fib.upc.edu/api/aules/places-lliures.json";
    
    void lectura();
    
private slots:
    void timerEvent(QTimerEvent *event);
    
    void dayUpdate();
    
    void downloaded(QNetworkReply *rep);
    
    void error(QNetworkReply::NetworkError code);
    
};

#endif // MAINCLASS
