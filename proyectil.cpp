#include "proyectil.h"
#include "drop.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QGraphicsRectItem>
#include <QPen>
#include <QBrush>
#include <QObject>


proyectil::proyectil()
{
    QPen p(Qt::red,1);
    QBrush b(Qt::yellow);
    setRect(0,0,5,15);
    setPen(p); setBrush(b);
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(10);


}

proyectil::~proyectil()
{
    delete timer;
}

void proyectil::move(){
    QList<QGraphicsItem *> colliding_items = collidingItems();

        // if one of the colliding items is an Enemy, destroy both the bullet and the enemy
        for (int i = 0, n = colliding_items.size(); i < n; ++i){

            //if(typeof(*(colliding_items[i]))==typeof(hola)){


                // remove them from the scene (still on the heap)
                scene()->removeItem(colliding_items[i]);
                scene()->removeItem(this);

                // delete them from the heap to save memory
                delete colliding_items[i];
                delete this;

                // return (all code below refers to a non existint bullet)
                return;
            //}
    }


    setPos(x(),y()-4);
    if(y()< 0){

        scene()->removeItem(this);
        delete this;
    }
}

