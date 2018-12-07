#include "jugador.h"


jugador::jugador(QList<proyectil*>* listeishon)
{

    setPixmap(QPixmap(":/images/peque3.png"));

    power=3;
    setVidaMax(1000);
    shot = new QMediaPlayer;
    shot->setMedia(QUrl("qrc:/music/shot1.mp3"));

    lista = listeishon;
    setVida(1000);

}


void jugador::shoot()
{

    if(shot->state()==QMediaPlayer::PlayingState){
        shot->setPosition(0);
    }

    else if(shot->state()==QMediaPlayer::StoppedState){
        shot->play();

    }
    if(Power()==1){
        shot->setMedia(QUrl("qrc:/music/shot1.mp3"));
        proyectil* bala = new proyectil;
        lista->push_back(bala);
        shot->play();

        bala->setPos(x()+35,y()-16);
        scene()->addItem(bala);
    }
    else if(Power()==2){
        shot->setMedia(QUrl("qrc:/music/shot2.mp3"));
        shot->play();
        proyectil* bala = new proyectil;
        proyectil* bala2 = new proyectil;
        lista->push_back(bala);
        lista->push_back(bala2);

        bala->setPos(x()+5,y()-16);
        scene()->addItem(bala);
        bala2->setPos(x()+70,y()-16);
        scene()->addItem(bala2);
    }
    else if(Power()==3){
        shot->setMedia(QUrl("qrc:/music/shot3.mp3"));
        shot->play();
        proyectil* bala = new proyectil;
        proyectil* bala2 = new proyectil;
        proyectil* bala3 = new proyectil;
        lista->push_back(bala);
        lista->push_back(bala2);
        lista->push_back(bala3);


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



}



personaje::personaje(){

    vida= 100000;
  }
