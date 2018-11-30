#ifndef JUGADOR_H
#define JUGADOR_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMediaPlayer>
#include <QGraphicsTextItem>
#include <QTimer>
#include "salud.h"



class jugador: public QObject,
               public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    jugador();
    void keyPressEvent(QKeyEvent *event) ;
    void keyReleaseEvent(QKeyEvent *ev) ;
    void shoot();
    ~jugador();

private:
    QMediaPlayer * shot, *whoosh;
    //salud *saludText;
    QTimer* timer;
    QTimer * timer2;
    QMap<int,bool>keys;
    int vida, power;
public slots:
    void spawn();
    void timeOutEvent();

};

#endif // JUGADOR_H
