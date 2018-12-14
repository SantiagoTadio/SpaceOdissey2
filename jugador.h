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
#include <QList>
#include "canon.h"


class personaje: public QObject,
                 public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    personaje();

    int Vida(){return vida;}
    void setVida(int v){vida=v;}
    void setVillano(string n);
    void Activo(bool a);
    
    string nombre;






private:
    int vida;


};



class jugador: public QObject,
        public QGraphicsPixmapItem
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
    int Vida(){return vida;}
    void setVida(int v){vida=v;  if(v>vidaMax)vida=vidaMax;}

private:
    int power,vidaMax, vida;
    QList<proyectil*> *lista;
    QMediaPlayer * shot;

};

#endif // JUGADOR_H
