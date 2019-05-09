#include "registro.h"
#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen * splash= new QSplashScreen; // imagen que sale al ejecutar el juego
    splash->setPixmap(QPixmap(":/images/spacesplash.png"));
    splash->show();
    registro w;

    QTimer::singleShot(2500,splash,SLOT(close()));
    QTimer::singleShot(2500,&w,SLOT(show()));


    return a.exec();
}
