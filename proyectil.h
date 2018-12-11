#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <iostream>

#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QGraphicsRectItem>
#include <QPen>
#include <QBrush>
#include <QObject>


using namespace std;

class proyectil: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    proyectil();

    int Efecto(){return valor;}

    void setEfecto(int e){valor = e;}


private:

    int valor;

public slots:
    void move();



};



class drop: public QObject, public QGraphicsPixmapItem

{
    Q_OBJECT
public:
    drop(bool asteroide);
    string Type(){return ID;}
    int Efecto(){return valor;}
    void setType(string t);
    void setEfecto(int e){valor = e;}

    float VelX(){return velX;}
    float VelY(){return velY;}
    void setVel(float vx, float vy){velX= vx;  velY = vy;}

private:
    string ID;
    int valor;
    float velX, velY;

public slots:
    void move(float dt,int posX, int posY, int posX2=10000, int posY2=10000);
    void move(){setPos(x(),y()+5);}
    void moveBack(float dt,int posX, int posY, int posX2=10000, int posY2=10000);




};


#endif // PROYECTIL_H
