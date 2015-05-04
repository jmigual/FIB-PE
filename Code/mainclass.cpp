#include "mainclass.h"


MainClass::MainClass(int argc, char *argv[]) :
    _acc(new QNetworkAccessManager),
    _fileD("./dataD.out"),
    _fileW("./data.txt")
{

    for (int i = 0; i < argc; ++i) qDebug() << argv[i];


    // Download configuration
    _req.setUrl(QUrl(_url));
    connect(_acc, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(downloaded(QNetworkReply*)));
    
    // Timer event configuration
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

    rep->disconnect();
    rep->deleteLater();
    
    QJsonDocument json(QJsonDocument::fromJson(data));
    qDebug() << _dataPC;
}

void MainClass::error(QNetworkReply::NetworkError code)
{
    cerr << "Error code: " << code << endl;
    
    // Hola he afegit un canvi
}
