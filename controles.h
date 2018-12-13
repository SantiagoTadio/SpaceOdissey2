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
    void setMultiplayer(bool p){multiplayer=p;}

public slots:
    void timeOutEvent();
    void setTrue1(){shoot1=true;}
    void setTrue2(){shoot2=true;}
private:
    QMap<int,bool>keys;
    bool on, multiplayer, shoot1, shoot2;


};

#endif // CONTROLES_H
