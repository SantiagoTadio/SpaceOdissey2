#ifndef CONTROLES_H
#define CONTROLES_H

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>
#include "jugador.h"
#include <QObject>



class controles: public QObject,public QGraphicsRectItem

{
    Q_OBJECT
public:
    controles();
    void keyPressEvent(QKeyEvent *event){keys[event->key()]=true; }
    void keyReleaseEvent(QKeyEvent *ev) {keys[ev->key()]=false; }
    jugador* pj1, *pj2;
    QTimer* timer = new QTimer;
    void encendido(bool x){on=x;}

public slots:
    void timeOutEvent();

private:
    QMap<int,bool>keys;
    bool on;


};

#endif // CONTROLES_H
