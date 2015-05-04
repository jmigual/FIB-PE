#include "mainclass.h"


MainClass::MainClass(int argc, char *argv[]) :
    _acc(new QNetworkAccessManager),
    _fileD("./dataD.out"),
    _fileW("./data.txt")
{

    for (int i = 0; i < argc; ++i) qDebug() << argv[i];
    
    for (QString &s : _className) _classe.insert(s, QVector<bool>(24, false));
    
    // Download configuration
    _req.setUrl(QUrl(_url));
    connect(_acc, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(downloaded(QNetworkReply*)));
    
    QTime day(QTime::currentTime());
    _timer.setInterval(_timeD + day.msecsTo(QTime(7, 58, 00)));
    connect(&_timer, SIGNAL(timeout()), this, SLOT(dayUpdate()));
    _timer.start();
    this->dayUpdate();
}

MainClass::~MainClass()
{
    delete _acc;
}

void MainClass::timerEvent(QTimerEvent *event)
{
    QTime t(QTime::currentTime());
    if (t > QTime(21, 0, 5) && event != NULL) {
        this->killTimer(event->timerId());
        return;
    }
    
    cout << "Downloading" << endl;
    _rep =_acc->get(_req);
    connect(_rep, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(error(QNetworkReply::NetworkError)));
}

void MainClass::dayUpdate()
{
    _timer.stop();
    _timer.setInterval(_timeD);
    _timer.start();
    
    
    for (QVector< bool > &V : _classe) for (bool &b : V) b = false;
    
    
    for (const QString &s : _className) {
        QUrl url("https://raco.fib.upc.edu/api/aules/disponibilitat-pc.txt");
        QUrlQuery query;
        query.addQueryItem("pc", s);
        url.setQuery(query);
        QNetworkRequest req(url);
        
        _rep = _acc->get(req);
        connect(_rep, SIGNAL(error(QNetworkReply::NetworkError)),
                this, SLOT(error(QNetworkReply::NetworkError)));
    }
    
    // Attack timer enable
    this->startTimer(_time);
}


void MainClass::downloaded(QNetworkReply *rep)
{
    cout << "Downloaded" << " ";
    QByteArray data = rep->readAll();

    rep->disconnect();
    rep->deleteLater();
    
    
    if (rep->url() == QUrl(_url)) {
        QJsonDocument jsonD(QJsonDocument::fromJson(data));
        QFile dFile(_fileD);
        
        if (!dFile.open(QIODevice::Append)) 
            cerr << "Error opening downloads file" << endl;
        
        dFile.write(jsonD.toJson(QJsonDocument::Compact));
        dFile.write("\n\n");
        
        QJsonObject json = jsonD.object();
        
        QJsonArray arr = json.value("aules").toArray();
        QString hora = json.value("update").toString("");
        
        // _fileW => End file data
        QFile file(_fileW);
        file.open(QIODevice::Append);
        QTextStream out(&file);
        out << hora << " " << arr.size() - 1 << endl;
        cout << hora << " " << arr.size() - 1 << " ";
        QDateTime date(QDateTime::fromString(hora, "dd/MM/yyyy hh:mm:ss"));
        int h =  date.time().hour();
        
        for (int i = 1; i < arr.size(); ++i) {
            QJsonObject obj = arr[i].toObject();
            QString aula = obj.value("nom").toString("").toUpper();
            int num = obj.value("places").toString("").toInt();
            out << aula << " " << num << " ";
            out << _classe[aula][h] << endl;
        }
        
    } 
    else {
        QString aula = rep->url().query().remove(0, 3);
        cout << aula << endl;
        QTextStream text(&data);
        text.readLine();
        QString hora = text.readLine();
        while (not text.atEnd()) {
            hora.truncate(2);
            unsigned int h = hora.toInt();
            
            Q_ASSERT(h >= 8 && h <= 21);
            _classe[aula][h] = true;
            
            hora = text.readLine();            
        }
    }
}

void MainClass::error(QNetworkReply::NetworkError code)
{
    cerr << "Error code: " << code << endl;
}
