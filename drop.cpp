#include "drop.h"
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

drop::drop()
{

    cont = 10;
    int tipo = rand()%5;

    if(tipo==4){
        setPixmap(QPixmap(":/images/fireball_big2.png"));
        vel = 2;
    }
    else {
        setPixmap(QPixmap(":/images/fireball_small2.png"));
        vel= 3;
    }

    timer = new QTimer;
    timer->start(20);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
}

drop::~drop()
{
    delete timer;
}

void drop::move()
{
    if(cont<=20) setPos(x()+vel,y()+vel);
    else setPos(x()-vel,y()+vel);
    cont++;
    if(cont==41) cont=0;

    if(y()>501){
        scene()->removeItem(this);

        delete this;
    }

}
