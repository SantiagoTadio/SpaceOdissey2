#include "proyectil.h"
#include <QObject>



proyectil::proyectil()
{
    //caracteristicas visuales de la bala
    QPen p(Qt::red,1); //borde rojo
    QBrush b(Qt::yellow); //relleno amarillo
    setRect(0,0,5,15); //dimensiones del rectángulo
    setPen(p); setBrush(b);
    valor= 100;
    friendly=true; //bala aliada (hace daño solo a enemigos)


    
}

void proyectil::setMalo(int efecto)//corrompe una bala, haciendo que ataque a los jugadores
{
    valor = efecto;
    friendly= false;
    QPen p(Qt::darkMagenta,2);
    QBrush b(Qt::cyan);
    setRect(0,0,8,20);//dimensiones de la bala
    setPen(p); setBrush(b); //borde magenta, fondo cyan
}

void drop::setType(string t)
{
    //cambia el valor del efecto de un drop y su imagen dependiendo del tipo
    ID=t; //tipo de drop
    if(t=="asteroideB"){
        setPixmap(QPixmap(":/images/fireball_big2.png"));

        valor=100;
    }
    else if(t=="asteroideS"){
        setPixmap(QPixmap(":/images/fireball_small2.png"));

        valor=30;
    }
    else if(t=="cura"){
        setPixmap(QPixmap(":/images/cura3.png"));
    }
    else if(t=="veneno"){
        setPixmap(QPixmap(":/images/damage.png"));
    }
    else if(t=="mejora"){
        setPixmap(QPixmap(":/images/powerUP.png"));
    }
    else if(t=="escudo"){
        setPixmap(QPixmap(":/images/Sin título-1.png"));
    }
}


void proyectil::move(){
    if(friendly) //si es bala aliada se mueve hacia arriba
    setPos(x(),y()-15);
    else //si es bala enemiga, se mueve hacia abajo
    setPos(x(),y()+15);  
    
}




drop::drop(bool asteroide)
{

    velX =0;
    velY = -5;
    int tipo = rand()%9;
    //aleatoriamente elige un numero de 0 a 9, para determinar el tipo de asteroide o poder que se crea
    if(asteroide){
        //si es un asteroide, se elige entre asteroide grande o pequeño
        if(tipo==0){
            ID = "asteroideB";//grande
            setPixmap(QPixmap(":/images/fireball_big2.png"));

            valor=100;
        }
        else {
            ID = "asteroideS";//pequeño
            setPixmap(QPixmap(":/images/fireball_small2.png"));

            valor=30;
        }
    }
    else{
        //si no es asteroide se elige entre:
        if(tipo==1){ //escudo, crea una barrera sobre la que rebotan los asteroides
            setPixmap(QPixmap(":/images/Sin título-1.png"));
            ID="escudo";
        }
        else if(tipo==2){//veneno, reduce la vida del jugador a la mitad
            setPixmap(QPixmap(":/images/damage.png"));
            ID="veneno";
        }
        else if(tipo==3){// crea un medio viscoso a través del cual pasan los asteroides de forma retardada
            setPixmap(QPixmap(":/images/antiG.png"));
            ID="gelato";
        }
        else if(tipo==4){ //agujero, crea un agujero negro que atrae a los asteroides
            setPixmap(QPixmap(":/images/hole.png"));
            ID="agujero";
        }
        else{ //cura, suma a la vida de los jugadores

            setPixmap(QPixmap(":/images/cura3.png"));
            ID="cura";

        }

    }

}


void drop::move( float dt,int posX, int posY, int posX2, int posY2) //movimiento acelerado de los asteroides hacia una o dos naves
{

    float Ax, Ay, angulo, rcuad, dx, dy;
    dx= posX-x();  dy= posY-y(); //halla la distancia vertical y horizontal entre las posiciones del jugador 1 y el asteroide
    rcuad = (dx*dx)+(dy*dy);
    angulo = atan2(dy,dx);//encuentra el ángulo del vector aceleración que apunta hacia la nave
    Ax+= (10000*cos(angulo))/rcuad;    Ay+= (10000*sin(angulo))/rcuad; //valores de las aceleraciones en dirección vertical y horizontal
    if(posX2!= 10000){
        dx= posX2-x();  dy= posY2-y();//halla la distancia vertical y horizontal entre las posiciones del jugador 2 y el asteroide
        rcuad = (dx*dx)+(dy*dy);
        angulo = atan2(dy,dx);//encuentra el ángulo del vector aceleración que apunta hacia la nave
        Ax+= (10000*cos(angulo))/rcuad;    Ay+= (10000*sin(angulo))/rcuad; //valores de las aceleraciones en dirección vertical y horizontal
    }


    velX += Ax* dt;   velY -= Ay*dt; //modifica las velocidades horizontal y vertical del asteroide
    setPos(int(x()+velX*dt+(Ax*(dt*dt)/2)),int(y()-(velY*dt+(Ay*(dt*dt)/2)))); //posiciona el asteroide en su nueva ubicación según su velocidad


}

