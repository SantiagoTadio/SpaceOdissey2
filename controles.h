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


class controles: public QObject,public QGraphicsRectItem //clase que recibe señales del teclado y/o arduino y ejecuta las órdenes de los jugadores

{
    Q_OBJECT
public:
    controles();
    ~controles();
    void keyPressEvent(QKeyEvent *event){keys[event->key()]=true; } // asigna el valor true a la tecla presionada en un mapa de enteros-booleanos
    void keyReleaseEvent(QKeyEvent *ev) {keys[ev->key()]=false; } // asigna el valor false a la tecla liberada en un mapa de enteros-booleanos
    jugador* pj1, *pj2; // jugador 1 y jugador 2
    QTimer* timer = new QTimer; //timer para la función timeOutEvent()
    void encendido(bool x){on=x;} // habilita las funciones del control
    void setMultiplayer(bool p){multiplayer=p;} // habilita el control para 1 o 2 jugadores
    void conectar(); // conecta el control por arduino
    void setvivo1(bool a){vivo1=a;} // jugador 1 vivo (vivo1=true)
    void setvivo2(bool a){vivo2=a;} //jugador 2 vivo (vivo2=true)

public slots:
    void timeOutEvent(); //funcion que busca las teclas activas en el mapa keys y ejecuta las ordenes respectivas
    void controlesArdu(); // recibe las señales del arduino y ejecuta las ordenes respectivas
    void setTrue1(){shoot1=true;} //booleano para habilitar los disparos del jugador 1
    void setTrue2(){shoot2=true;} //booleano para habilitar los disparos del jugador 2
private:
    QMap<int,bool>keys; // mapa que almacena las parejas int-bool correspondientes a teclas del teclado y su estado; presionada(true) o suelta(false)
    bool on, multiplayer, shoot1, shoot2,vivo1,vivo2;
    QSerialPort *cont= new QSerialPort;
    QTimer* ardu= new QTimer; // timer para leer las señales que envía el arduino

};

#endif // CONTROLES_H
