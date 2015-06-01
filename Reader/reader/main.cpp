#include <QCoreApplication>
#include <QDate>
#include <QDateTime>
#include <QTextStream>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    if (argc <= 2) {
        qWarning() << "Error, no output file loaded";
        return 0;
    }
    
    QFile f(argv[1]);
    f.open(QIODevice::ReadOnly);
    QTextStream cin(&f);
    
    QString dat0;
    QString dat1;
    QString fi("$");
    cin >> dat0;
    while(dat0 != fi) {
        cin >> dat1;
        dat0 += dat1;
        break;
        
        cin >> dat0;
    }
    qDebug() << dat0 << dat1;
    
    return;
}
