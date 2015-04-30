#include <QCoreApplication>
#include <QThread>

#define MINTUS  15          // 15 minuts
#define TEMPS   MINUTS*60   // passem a segons


void lectura()
{
    QUrl url("https://raco.fib.upc.edu/api/aules/places-lliures.json");
    QNetworkRequest req(url);
    
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QObject::connect();
    while(1) {
        
        
        // Esperem un cert temps
        QThread::sleep(TEMPS);
    }
    
    return a.exec();
}
