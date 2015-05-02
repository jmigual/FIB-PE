#include <QCoreApplication>
#include <QThread>
#include "mainclass.h"

#define MINTUS  15          // 15 minuts
#define TEMPS   MINUTS*60   // passem a segons


void lectura()
{
    
    
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MainClass m(argc, argv);
    
    return a.exec();
}
