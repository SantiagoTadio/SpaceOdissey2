#include "registro.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    registro w;
    w.show();

    return a.exec();
}
