#ifndef UNODOS_H
#define UNODOS_H

#include <string>
#include <iostream>
#include <QDialog>
#include <fstream>
#include "mainwindow.h"
#include <QGraphicsScene>

using namespace std;

namespace Ui {
class UnoDos;
}

class UnoDos : public QDialog
// Dialogo para seleccionar un juagador o multijugador
{
    Q_OBJECT

public:
    explicit UnoDos(QWidget *parent = nullptr);
    ~UnoDos();
    void setalias(string alias); // Asigna el alias del usuario

    void setchek(int _chek); // Asigna el numero de partida


private slots:
    void on_uno_clicked(); // crea informacion de partida para un jugador

    void on_dos_clicked(); // crea informacion de partida para dos jugadores

private:
    Ui::UnoDos *ui;
    string alias_Usu_jug;
    QGraphicsScene* escena= new QGraphicsScene;
    int chek;
};

#endif // UNODOS_H
