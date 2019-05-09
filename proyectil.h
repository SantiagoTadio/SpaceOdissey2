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

class proyectil: public QObject, public QGraphicsRectItem // balas aliadas y enemigas

{
    Q_OBJECT
public:
    proyectil();

    int Efecto(){return valor;} // valor del daño que causa al contacto
    void setMalo(int efecto); // convierte la bala en enemiga
    void setEfecto(int e){valor = e;} // asigna un valor al daño
    bool Friendly(){return friendly;} // averigua si una bala es aliada o enemiga


private:

    int valor;
    bool friendly;

public slots:
    void move(); // funcion que asigna una nueva posición al proyectil



};



class drop: public QObject, public QGraphicsPixmapItem // asteroides y poderes

{
    Q_OBJECT
public:
    drop(bool asteroide); // crea un asteroide si asteroide=true. De lo contrario, crea aleatoriamente un poder
    string Type(){return ID;} // retorna el tipo de proyectil
    int Efecto(){return valor;} // retorna el valor del daño o efecto que causa el proyectil
    void setType(string t); // asigna el tipo al proyectil
    void setEfecto(int e){valor = e;} // asigna el efecto al proyectil

    float VelX(){return velX;} // velocidad horizontal del proyectil
    float VelY(){return velY;} // velocidad vertical del proyectil
    void setVel(float vx, float vy){velX= vx;  velY = vy;} // asigna velocidades horizontal y vertical del proyectil

private:
    string ID;
    int valor;
    float velX, velY;

public slots:
    void move(float dt,int posX, int posY, int posX2=10000, int posY2=10000); // movimiento acelerado de atracci de los asteroides
    void move(){setPos(x(),y()+5);} // movimiento rectilíneo uniforme de las balas
    void moveBack(float dt,int posX, int posY, int posX2=10000, int posY2=10000); // movimiento acelerado de repulsión de los asteroides




};


#endif // PROYECTIL_H
