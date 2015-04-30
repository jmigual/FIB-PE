#include <QCoreApplication>
#include <QThread>
#include <QUrl>

#define MINTUS  15          // 15 minuts
#define TEMPS   MINUTS*60   // passem a segons

void lectura()
{
    QUrl("https://raco.fib.upc.edu/api/aules/places-lliures.json");
    
    
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    while(1) {
        lectura();
        
        // Esperem un cert temps
        QThread::sleep(TEMPS);
    }
    
    return a.exec();
}
