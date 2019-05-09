#include "jugador.h"


jugador::jugador(QList<proyectil*>* listeishon) //recibe la dirección a la lista de proyectiles
{

    setPixmap(QPixmap(":/images/peque3.png")); // imagen de la nave

    power=1; //nivel de poder inicial
    setVidaMax(1000); //nivel de vida máxima
    shot = new QMediaPlayer;
    shot->setMedia(QUrl("qrc:/music/shot1.mp3")); // sonido de disparo
    
    lista = listeishon;
    setVida(1000); // nivel de vida inicial

}


void jugador::shoot()
{

    if(shot->state()==QMediaPlayer::PlayingState){
        shot->setPosition(0); //reinicia el sonido de disparo
    }

    else if(shot->state()==QMediaPlayer::StoppedState){
        shot->play(); // reproduce el sonido de disparo

    }
    // sonido, posicion y ubicación de las balas en función del nivel de poder de la nave
    if(Power()==1){
        shot->setMedia(QUrl("qrc:/music/shot1.mp3"));
        proyectil* bala = new proyectil;
        lista->push_back(bala);
        shot->play();

        bala->setPos(x()+35,y()-16); //justo arriba de la nave, y centrada
        scene()->addItem(bala);
    }
    else if(Power()==2){
        shot->setMedia(QUrl("qrc:/music/shot2.mp3"));
        shot->play();
        proyectil* bala = new proyectil;
        proyectil* bala2 = new proyectil;
        lista->push_back(bala);
        lista->push_back(bala2);

        //arriba de la nave, distribuidas simétricamente a la derecha e izquierda del centro de la nave
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

        //arriba de la nave, una en el centro y las otras dos distribuidas simétricamente a la derecha e izquierda del centro de la nave
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
    delete lista;


}



personaje::personaje(){

    vida= 5000;
    nombre = "augusGalactus";
    setPos(260,20);
    setPixmap(QPixmap(":/images/jefeGus.png"));
    

}

void personaje::setVillano(string n)
{
    nombre = n;
    //inicializa la vida y la apariencia del jefe dependiendo de su nombre
    if(n=="augusGalactus"){
        setPixmap(QPixmap(":/images/jefeGus.png"));
        setVida(5000);
    }
    else if(n=="augusGalactus2"){
        setPixmap(QPixmap(":/images/jefeGus2.png"));
        setVida(10000);
    }
    else if(n=="augusGalactus3"){
        setPixmap(QPixmap(":/images/jefeGus3.png"));
        setVida(20000);
    }
}

void personaje::setVillano()
{

    //inicializa la vida y la apariencia del jefe dependiendo de su nombre
    if(nombre=="augusGalactus"){
        setPixmap(QPixmap(":/images/jefeGus.png"));
        setVida(5000);
    }
    else if(nombre=="augusGalactus2"){
        setPixmap(QPixmap(":/images/jefeGus2.png"));
        setVida(10000);
    }
    else if(nombre=="augusGalactus3"){
        setPixmap(QPixmap(":/images/jefeGus3.png"));
        setVida(20000);
    }
}

int personaje::vidaCanon()
{
    if(nombre=="augusGalactus"){

        return(1000);
    }
    else if(nombre=="augusGalactus2"){

        return(2000);
    }
    else if(nombre=="augusGalactus3"){

        return(4000);
    }
}
