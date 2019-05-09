#ifndef MENUPAUSA_H
#define MENUPAUSA_H

#include <QDialog>
#include "mainwindow.h"
#include "registro.h"
#include "inicio.h"
#include <QGraphicsScene>

namespace Ui {
class MenuPausa; // menú de pausa del juego, y opciones de juego.
}

class MenuPausa : public QDialog
{
    Q_OBJECT

public:
    explicit MenuPausa(QWidget *parent = nullptr);
    ~MenuPausa();
    void setmain(MainWindow *m){mai=m;}
    void esconder(); // funcion que esconde las opciones de guardar y reanudar partida en caso de que el menú se abra despues de la muerte de los jugadores


private slots:
    void on_guardar_clicked(); // llama la función que guarda los datos de la partida actual en el archivo de texto correspondiente

    void on_partidas_clicked();// llama la función que despliega el menú de selección de partida

    void on_inicio_clicked(); // llama la función que redirecciona al usuario a la pantalla de inicio

    void on_salir_clicked(); // cierra el juego

    void on_reanudar_clicked(); // continúa el juego donde estaba

private:
    Ui::MenuPausa *ui;
    QGraphicsScene* escena= new QGraphicsScene;
    MainWindow *mai;

};

#endif // MENUPAUSA_H
