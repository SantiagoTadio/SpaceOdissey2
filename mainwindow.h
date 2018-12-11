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




private:
    Ui::MainWindow *ui;
    controles * control = new controles;
    QGraphicsScene * scene;

    QList<proyectil*> balas;
    QList<drop*> drops;
    QList<drop*> pows;

    jugador * player1 = new jugador(&balas);
    jugador * player2 = new jugador(&balas);
    personaje * jefe = new personaje;
    QGraphicsRectItem * escudo= new QGraphicsRectItem, * gelatina= new QGraphicsRectItem;

    QTimer * animacion = new QTimer;
    QTimer * spawning = new QTimer;
    QTimer * powers = new QTimer;

    QMediaPlayer * musica = new QMediaPlayer;

    bool singlePlayer, bossOn;
    int puntaje=0;
    string partida;

};

#endif // MAINWINDOW_H
