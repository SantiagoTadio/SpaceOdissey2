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
            if(shoot1){
                pj1->shoot();
                shoot1=false;
                QTimer::singleShot((150*pj1->Power()),this,SLOT(setTrue1()));
            }
        }


        if(multiplayer){
            if(keys[Qt::Key_A]&& pj2->x()>10){
                pj2->setPos(pj2->x()-10,pj2->y());
            }
            if(keys[Qt::Key_D]&& pj2->x()<730){
                pj2->setPos(pj2->x()+10,pj2->y());
            }
            if(keys[Qt::Key_Control]){
                if(shoot2){
                     pj2->shoot();
                     shoot2=false;
                     QTimer::singleShot((150*pj2->Power()),this,SLOT(setTrue2()));
                }

            }
        }

    }



}

controles::controles(){
    timer->start(50);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeOutEvent()));
    on=true;  multiplayer=false;  shoot1=true;   shoot2=true;
}
