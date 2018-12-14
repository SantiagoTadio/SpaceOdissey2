#ifndef CONTROLES_H
#define CONTROLES_H

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>
#include "jugador.h"
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QFileDialog>
#include <QDebug>
#include <QTextStream>


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
    void conectar();
    void setvivo1(bool a){vivo1=a;}
    void setvivo2(bool a){vivo2=a;}

public slots:
    void timeOutEvent();
    void controlesArdu();
    void setTrue1(){shoot1=true;}
    void setTrue2(){shoot2=true;}
private:
    QMap<int,bool>keys;
    bool on, multiplayer, shoot1, shoot2,vivo1,vivo2;
    QSerialPort *cont= new QSerialPort;
    QTimer* ardu= new QTimer;

};

#endif // CONTROLES_H
