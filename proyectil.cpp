#include "proyectil.h"
#include <QObject>



proyectil::proyectil()
{
    QPen p(Qt::red,1);
    QBrush b(Qt::yellow);
    setRect(0,0,5,15);
    setPen(p); setBrush(b);
    valor= 100;



}

void drop::setType(string t)
{
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

    setPos(x(),y()-15);

}




drop::drop(bool asteroide)
{

    velX =0;
    velY = -5;
    int tipo = rand()%9;
    if(asteroide){

        if(tipo==0){
            ID = "asteroideB";
            setPixmap(QPixmap(":/images/fireball_big2.png"));

            valor=100;
        }
        else {
            ID = "asteroideS";
            setPixmap(QPixmap(":/images/fireball_small2.png"));

            valor=30;
        }
    }
    else{
        if(tipo==0){
            setPixmap(QPixmap(":/images/powerUP.png"));
            ID="mejora";
        }
        else if(tipo==1){
            setPixmap(QPixmap(":/images/Sin título-1.png"));
            ID="escudo";
        }
        else if(tipo==2){
            setPixmap(QPixmap(":/images/damage.png"));
            ID="veneno";
        }
        else if(tipo==3){
            setPixmap(QPixmap(":/images/antiG.png"));
            ID="gelato";
        }
        else if(tipo==4){
            setPixmap(QPixmap(":/images/hole.png"));
            ID="agujero";
        }
        else{

            setPixmap(QPixmap(":/images/cura3.png"));
            ID="cura";

        }

    }

}


void drop::move( float dt,int posX, int posY, int posX2, int posY2)
{

    float Ax, Ay, angulo, rcuad, dx, dy;
    dx= posX-x();  dy= posY-y();
    rcuad = (dx*dx)+(dy*dy);
    angulo = atan2(dy,dx);
    Ax+= (10000*cos(angulo))/rcuad;    Ay+= (10000*sin(angulo))/rcuad;
    if(posX2!= 10000){
        dx= posX2-x();  dy= posY2-y();
        rcuad = (dx*dx)+(dy*dy);
        angulo = atan2(dy,dx);
        Ax+= (10000*cos(angulo))/rcuad;    Ay+= (10000*sin(angulo))/rcuad;
    }


    velX += Ax* dt;   velY -= Ay*dt;
    setPos(int(x()+velX*dt+(Ax*(dt*dt)/2)),int(y()-(velY*dt+(Ay*(dt*dt)/2))));


}

void drop::moveBack(float dt, int posX, int posY, int posX2, int posY2)
{
    float Ax, Ay, angulo, rcuad, dx, dy;
    dx= posX-x();  dy= posY-y();
    rcuad = (dx*dx)+(dy*dy);
    angulo = atan2(dy,dx);
    Ax+= (10000*cos(angulo))/rcuad;    Ay+= (10000*sin(angulo))/rcuad;
    if(posX2!= 10000){
        dx= posX2-x();  dy= posY2-y();
        rcuad = (dx*dx)+(dy*dy);
        angulo = atan2(dy,dx);
        Ax+= (10000*cos(angulo))/rcuad;    Ay+= (10000*sin(angulo))/rcuad;
    }


    velX -= Ax* dt;   velY += Ay*dt;
    setPos(int(x()+velX*dt+(Ax*(dt*dt)/2)),int(y()-(velY*dt+(Ay*(dt*dt)/2))));
}

