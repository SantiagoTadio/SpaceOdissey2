#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include "jugador.h"
#include "proyectil.h"
#include <QMediaPlayer>
#include <QTimer>
#include "controles.h"
#include "usuario.h"
#include <QGraphicsRectItem>
#include <fstream>
#include <sstream>
#include <math.h>
#include "canon.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
// animacion, funciones principales
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    string Partida(){return partida;} // Retorna el nombre de la partida que esta jugando
    void BossActive(bool t); // Activa(aparece) o desactiva(desaparace) al jefe
    int numero;// numero es la variable que alterna las imágenes de las naves, para crear el efecto de destello

public slots:

    void spawn(); // Se crean los asteroides
    void animar(); // Recorre las listas de objetos y hace la animacion
    void on_pushButton_clicked(); // Activa la funcion pausa
    void pausa(); // Hinabilita las funciones principales del juego y abre el diaglogo MenuPausa
    void reanudar(); // Restablece el funcionamiento del juego
    void guardarDatos(); // Almacena los datos de la partida en el archivo de texto correspondiente
    void cargarDatos(); // Obtiene la informacion de la partida guardada en el archivo de texto
    void setPartida(string p){partida=p;} // Asigna el nombre del archivo de texto correspondiente a la partida escogida
    void crearPoder(); // Se crean los poderes aleatoriamente(escudo, mejora de vida, etc)
    void esconderRecto(); // Deshabilita el poder escudo
    void esconderGelato(); // Deshabilita el poder gelato(gelatina viscosa)
    void esconderAgujero(); // Deshabilita el agujero negro
    void shoot(); // Dispara balas enemigas
    void sortear(); // Sortea que nave del jefe se va a deshabilitar
    void setCanones(); // crea el jefe y los canones



private slots:
    void on_pushButton_2_clicked(); // Llama a la funcion conectar de control

private:
    Ui::MainWindow *ui;
    controles * control = new controles; // crea el control de las naves
    QGraphicsScene * scene;

    QList<proyectil*> balas; // lista de proyectiles disparados por las naves
    QList<proyectil*> balasEnemigas; //lista de proyectiles disparados por las naves enemigas
    QList<drop*> drops; // lista de asteroides
    QList<drop*> pows; //lista de poderes
    QList<canon*> canones; // lista de naves enemigas

    //listas de objetos que se eliminarán del juego
    QList<drop*> BasuraDrops;
    QList<drop*> BasuraPows;
    QList<proyectil*> BasuraBalas;
    QList<proyectil*> BasuraEnemigas;

    // creacion de los jugadores, con un puntero a la lista de balas
    jugador * player1 = new jugador(&balas);
    jugador * player2 = new jugador(&balas);

    personaje * jefe = new personaje; // creacion del jefe
    // creacion de los objetos activables (escudo, viscocidad y agujero negro)
    QGraphicsRectItem * recto= new QGraphicsRectItem, *gelato= new QGraphicsRectItem;
    QGraphicsEllipseItem * hole= new QGraphicsEllipseItem;

    // timers para controlar la creación, movimiento, acciones y colisiones de los objetos en la escena
    QTimer * animacion = new QTimer;
    QTimer * spawning = new QTimer;
    QTimer * powers = new QTimer;
    QTimer* sorteo= new QTimer;
    QTimer* disparar= new QTimer;

    QMediaPlayer * musica = new QMediaPlayer; //reproductor de musica

    bool singlePlayer, bossOn, holeOn;
    int puntaje=0, CanonPausado;
    string partida;

};

#endif // MAINWINDOW_H
