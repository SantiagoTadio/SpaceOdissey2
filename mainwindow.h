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
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    string Partida(){return partida;}
    void BossActive(bool t);

public slots:

    void spawn();
    void animar();
    void on_pushButton_clicked();
    void pausa();
    void reanudar();
    void guardarDatos();
    void cargarDatos();
    void setPartida(string p){partida=p;}
    void crearPoder();
    void esconderRecto();
    void esconderGelato();
    void esconderAgujero();
    void shoot();
    void sortear();
    void setCanones();



private slots:
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    controles * control = new controles;
    QGraphicsScene * scene;

    QList<proyectil*> balas;
    QList<proyectil*> balasEnemigas;
    QList<drop*> drops;
    QList<drop*> pows;
    QList<canon*> canones;

    QList<drop*> BasuraDrops;
    QList<drop*> BasuraPows;
    QList<proyectil*> BasuraBalas;
    QList<proyectil*> BasuraEnemigas;

    jugador * player1 = new jugador(&balas);
    jugador * player2 = new jugador(&balas);
    personaje * jefe = new personaje;
    QGraphicsRectItem * recto= new QGraphicsRectItem, *gelato= new QGraphicsRectItem;
    QGraphicsEllipseItem * hole= new QGraphicsEllipseItem;

    QTimer * animacion = new QTimer;
    QTimer * spawning = new QTimer;
    QTimer * powers = new QTimer;



    QTimer* sorteo= new QTimer;
    QTimer* disparar= new QTimer;

    QMediaPlayer * musica = new QMediaPlayer;

    bool singlePlayer, bossOn, holeOn;
    int puntaje=0, CanonPausado;
    string partida;

};

#endif // MAINWINDOW_H
