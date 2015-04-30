#ifndef DOWNLOADER
#define DOWNLOADER

#include <QObject>
#include <QtNetwork>

class Downloader : QObject
{
    Q_OBJECT
    
public:
    Downloader();
    
    ~Downloader();
    
    void download(QString);
    
signals:
    void downloaded(QString);
    
private:
    
    QNetworkAccessManager _acc;
    
private slots:
    
    void downloaded(QNetworkReply *);
};

#endif // DOWNLOADER

