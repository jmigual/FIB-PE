#include "mainclass.h"


MainClass::MainClass() :
    _acc(new QNetworkAccessManager)
{
    _req.setUrl(QUrl(_url));
    connect(_acc, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(downloaded(QNetworkReply*)));
}

MainClass::~MainClass()
{
    delete _acc;
}

void MainClass::start()
{
    cout << "Starting download" << endl;
    download();
}

void MainClass::download()
{
    cout << "Download called" << endl;
    _rep =_acc->get(_req);
    connect(_rep, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(error(QNetworkReply::NetworkError)));
}

void MainClass::downloaded(QNetworkReply *rep)
{
    cout << "Downloaded" << endl;
    QByteArray data = rep->readAll();
    rep->deleteLater();
    
    qDebug() << data;
}

void MainClass::error(QNetworkReply::NetworkError code)
{
    cerr << "Error code: " << code << endl;
}
