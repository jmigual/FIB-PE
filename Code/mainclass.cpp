#include "mainclass.h"


MainClass::MainClass() :
    _acc(new QNetworkAccessManager)
{
    _req.setUrl(QUrl(_url));
    connect(_acc, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(downloaded(QNetworkReply*)));
    
    this->startTimer(_time);
    
    timerEvent(NULL);
}

MainClass::~MainClass()
{
    delete _acc;
}

void MainClass::timerEvent(QTimerEvent *)
{
    cout << "Downloading" << endl;
    _rep =_acc->get(_req);
    connect(_rep, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(error(QNetworkReply::NetworkError)));
}


void MainClass::downloaded(QNetworkReply *rep)
{
    cout << "Downloaded" << endl;
    QByteArray data = rep->readAll();
    rep->deleteLater();
    
    QJsonDocument json(QJsonDocument::fromJson(data));
    _dataPC = json.object();
    qDebug() << _dataPC;
}

void MainClass::error(QNetworkReply::NetworkError code)
{
    cerr << "Error code: " << code << endl;
}
