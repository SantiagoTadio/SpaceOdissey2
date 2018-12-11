#ifndef JUGADOR_H
#define JUGADOR_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMediaPlayer>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsScene>
#include "proyectil.h"
#include <stdlib.h>
#include <time.h>


class personaje: public QObject,
                 public QGraphicsPixmapItem
{
public:
    personaje();
    void shoot();
    int Vida(){return vida;}
    void setVida(int v){vida=v;}



private:
    int vida;
};



class jugador: public personaje
{
    Q_OBJECT
public:
    jugador(QList<proyectil*>* listeishon);

    void shoot();
    ~jugador();
    int Power(){return power;}
    void setPoder(int p){if(p<4){power=p; vidaMax=1000*p; if(Vida()>vidaMax){setVida(vidaMax);}}}
    int VidaMax(){return vidaMax;}
    void setVidaMax(int v){vidaMax=v;}

private:
    int power,vidaMax;
    QList<proyectil*> *lista;
    QMediaPlayer * shot;

};

#endif // JUGADOR_H
