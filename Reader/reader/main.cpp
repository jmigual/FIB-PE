#include <QCoreApplication>
#include <QDate>
#include <QDateTime>
#include <QTextStream>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    if (argc <= 3) {
        qWarning() << "Error, no output file loaded";
        return 0;
    }
    
    QFile f1(argv[1]);
    f1.open(QIODevice::ReadOnly);
    QTextStream cin(&f1);
    
    QFile f2(argv[2]);
    f2.open(QIODevice::WriteOnly);
    QTextStream out1(&f2);
    
    QFile f3(argv[3]);
    f3.open(QIODevice::WriteOnly);
    QTextStream out2(&f3);
    
    QString dat0;
    QString dat1;
    
    while(not cin.atEnd()) {
        cin >> dat0;
        cin >> dat1;
        dat0 += " " + dat1;
        
        QDateTime d = QDateTime::fromString(dat0, "dd/MM/yyyy hh:mm:ss");
        dat0 = d.toString("dd/MM/yyyy hh:mm:ss");
        
        int n;
        cin >> n;        
        uint nClasse = 0;
        uint sClasse = 0;
        
        
        for (int i = 0; i < n; ++i) {
            cin >> dat1;
            int temp;
            cin >> temp;
            int classe;
            cin >> classe;
            
            classe ? sClasse += temp : nClasse += temp;
        }
        
        out1 << dat0 << "\t" << nClasse << endl;
        out2 << dat0 << "\t" << sClasse << endl;
    }
    
    return 0;
}
