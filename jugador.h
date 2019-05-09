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
// villano
{
    Q_OBJECT
public:
    personaje();

    int Vida(){return vida;}
    void setVida(int v){vida=v;}
    void setVillano(string n); // nombre del villano
    void setVillano();
    int vidaCanon();
    void Activo(bool a); // villano activo en pantalla(true) o villano inactivo invisible(false)
    
    string nombre;






private:
    int vida;


};



class jugador: public QObject,
        public QGraphicsPixmapItem
//jugadores
{
    Q_OBJECT
public:
    jugador(QList<proyectil*>* listeishon); // Crea la nave y se asigna la lista en la que se van a ingresar los proyectiles que dispare

    void shoot(); // Crea un proyectil y lo añade a las lista
    ~jugador();
    int Power(){return power;} // Retorna el nivel de poder de la nave
    void setPoder(int p){if(p<4){power=p; vidaMax=1000*p; if(Vida()>vidaMax){setVida(vidaMax);}}} // Asigna un nivel de poder a la nave
    int VidaMax(){return vidaMax;} // Retorna la vida maxima de la nave
    void setVidaMax(int v){vidaMax=v;} // Asigna la vida maxima a la nave
    int Vida(){return vida;} // Retorna la vida de la nave
    void setVida(int v){vida=v;  if(v>vidaMax)vida=vidaMax;} // Asigna el nivel de vida a la nave asegurandose que no sobre pase el nivel de vida maxima

private:
    int power,vidaMax, vida;
    QList<proyectil*> *lista;
    QMediaPlayer * shot;

};

#endif // JUGADOR_H
