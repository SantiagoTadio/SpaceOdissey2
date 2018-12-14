#include "controles.h"
#include <QObject>


void controles::timeOutEvent()
{
    if(on){
        if(vivo1){
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
        }
        if(vivo2){
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



}

void controles::controlesArdu()
{
    if(on){
        char data;
        int l = 0;
        bool flag=true;
           if(cont->waitForReadyRead(100)){

                //Data was returned
                l = cont->read(&data,1);
                switch (data) {
                case 'I':
                      pj1->setPos(pj1->x()-10,pj1->y());
                    break;
                case 'D':
                       pj1->setPos(pj1->x()+10,pj1->y());
                    break;
                case 'S':
                    if(shoot1){
                        pj1->shoot();
                        shoot1=false;
                        QTimer::singleShot((150*pj1->Power()),this,SLOT(setTrue1()));
                    }
                    break;
                case 'i':
                    if(multiplayer)
                        pj2->setPos(pj2->x()-10,pj2->y());
                    break;
                case 'd':
                    if(multiplayer)pj2->setPos(pj2->x()+10,pj2->y());
                    break;
                case 's':
                    if(multiplayer){
                        if(shoot2){
                             pj2->shoot();
                             shoot2=false;
                             QTimer::singleShot((150*pj2->Power()),this,SLOT(setTrue2()));
                        }
                    }
                    break;
                case 'C':
                    ardu->stop();
                    cont->close();

                    break;

                default:
                    break;
                }

                qDebug()<<"Response: "<<data;
                flag=false;

            }else{
                //No data
                qDebug()<<"Time out";
          }
    }
}

controles::controles(){
    timer->start(50);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeOutEvent()));
    on=true;  multiplayer=false;  shoot1=true;   shoot2=true;  vivo1=true;    vivo2=true;
    connect(ardu,SIGNAL(timeout()),this,SLOT(controlesArdu()));
}

controles::~controles()
{
    delete timer;
    delete cont;
    delete ardu;
    delete pj1;
    delete pj2;
}

void controles::conectar()
{
    cont->setPortName("COM8");
    //timer_control->start(100);
    if(cont->open(QIODevice::ReadWrite)){
        //Ahora el puerto seria está abierto
        if(!cont->setBaudRate(QSerialPort::Baud9600)) //Configurar la tasa de baudios
            qDebug()<<cont->errorString();

        if(!cont->setDataBits(QSerialPort::Data8))
            qDebug()<<cont->errorString();

        if(!cont->setParity(QSerialPort::NoParity))
            qDebug()<<cont->errorString();

        if(!cont->setStopBits(QSerialPort::OneStop))
            qDebug()<<cont->errorString();

        if(!cont->setFlowControl(QSerialPort::NoFlowControl))
            qDebug()<<cont->errorString();
            ardu->start(20);
    }
    else{
        qDebug()<<"Serial COM8 not opened. Error: "<<cont->errorString();
    }
}
