#include "jugador.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include "proyectil.h"
#include "drop.h"
#include <stdlib.h>
#include <time.h>
#include <QTimer>
#include <QObject>
#include "salud.h"

jugador::jugador()
{

    setPixmap(QPixmap(":/images/peque3.png"));

    power = 3;
    shot = new QMediaPlayer;
    shot->setMedia(QUrl("qrc:/music/shot1.mp3"));

    whoosh = new QMediaPlayer;
    whoosh->setMedia(QUrl("qrc:/music/whoosh.mp3"));

    timer = new QTimer;
    timer->start(80);
    connect(timer,SIGNAL(timeout()),this,SLOT(spawn()));

    timer2 = new QTimer;
    timer2->start(50);
    connect(timer2,SIGNAL(timeout()),this,SLOT(timeOutEvent()));

    vida= 1000;

    //salud*saludText = new salud;
    //saludText->modificar(vida);

    //scene()->addItem(saludText);
    //saludText->setPos(30,30);


}
/*
void jugador::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Left && x()-30 >0){

        setPos(x()-20,y());
    }
    else if(event->key()==Qt::Key_Right && x()+100 < 821) {

        setPos(x()+20,y());
    }

    if(event->key()==Qt::Key_Space ){

        shoot();

        if(shot->state()==QMediaPlayer::PlayingState){
            shot->setPosition(0);
        }
        else if(shot->state()==QMediaPlayer::StoppedState){
            shot->play();
        }

    }

}
*/
void jugador::keyPressEvent(QKeyEvent *event){
    keys[event->key()]=true;

}
void jugador::keyReleaseEvent(QKeyEvent *ev){
    keys[ev->key()]=false;
}

void jugador::timeOutEvent(){
    if(keys[Qt::Key_Left]){
        setPos(x()-10,y());
    }
    if(keys[Qt::Key_Right]){
        setPos(x()+10,y());
    }
    if(keys[Qt::Key_Space]){
        shoot();
        if(shot->state()==QMediaPlayer::PlayingState){
            shot->setPosition(0);
        }
        else if(shot->state()==QMediaPlayer::StoppedState){
            shot->play();
        }
    }
}

void jugador::shoot()
{
    if(power==1){
        shot->setMedia(QUrl("qrc:/music/shot1.mp3"));
        proyectil* bala = new proyectil;

        bala->setPos(x()+35,y()-16);
        scene()->addItem(bala);
    }
    else if(power==2){
        shot->setMedia(QUrl("qrc:/music/shot2.mp3"));
        proyectil* bala = new proyectil;
        proyectil* bala2 = new proyectil;

        bala->setPos(x()+5,y()-16);
        scene()->addItem(bala);
        bala2->setPos(x()+70,y()-16);
        scene()->addItem(bala2);
    }
    else if(power==3){
        shot->setMedia(QUrl("qrc:/music/shot3.mp3"));
        proyectil* bala = new proyectil;
        proyectil* bala2 = new proyectil;
        proyectil* bala3 = new proyectil;


        bala->setPos(x()+5,y()-16);
        scene()->addItem(bala);
        bala2->setPos(x()+70,y()-16);
        scene()->addItem(bala2);
        bala3->setPos(x()+35,y()-16);
        scene()->addItem(bala3);
    }
}

jugador::~jugador()
{
    delete shot;
    delete timer;
    delete whoosh;


}

void jugador::spawn()
{
    int px = 90+rand()%631;
    drop * cosa = new drop;
    cosa->setPos(px,0);
    scene()->addItem(cosa);
}
