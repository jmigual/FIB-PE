#include <QCoreApplication>
#include <QThread>
#include "mainclass.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MainClass m(argc, argv);
    
    return a.exec();
}
