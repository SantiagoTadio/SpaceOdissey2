#include "controles.h"
#include <QObject>


void controles::timeOutEvent()
{
    if(on){
        if(keys[Qt::Key_Left]&& pj1->x()>10){
            pj1->setPos(pj1->x()-10,pj1->y());
        }
        if(keys[Qt::Key_Right]&& pj1->x()<730){
            pj1->setPos(pj1->x()+10,pj1->y());
        }
        if(keys[Qt::Key_Space]){
            pj1->shoot();
        }



        if(keys[Qt::Key_A]&& pj2->x()>10){
            pj2->setPos(pj2->x()-10,pj2->y());
        }
        if(keys[Qt::Key_D]&& pj2->x()<730){
            pj2->setPos(pj2->x()+10,pj2->y());
        }
        if(keys[Qt::Key_Control]){
            pj2->shoot();

        }
    }



}

controles::controles(){
    timer->start(50);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeOutEvent()));
    on=true;
}
