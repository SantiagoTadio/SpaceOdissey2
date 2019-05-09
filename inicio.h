#ifndef INICIO_H
#define INICIO_H
#include <string>
#include <iostream>
#include <QDialog>
#include <fstream>
#include "mainwindow.h"
#include "unodos.h"
#include <QGraphicsScene>

using namespace std;
namespace Ui {
class inicio;
}

class inicio : public QDialog // página de selección de partida
{
    Q_OBJECT

public:
    explicit inicio(QWidget *parent = nullptr);
    void setUsuario(string u){alias_Usu_jug=u;} // asigna el usuario seleccionado en la página anterior(registro)
    ~inicio();
    void cargarDatos(string datos); // en el dialogo inicio mira si hay una partida guardada
    void setchek(int _chek); // asigna la partida que indica _chek
    int getchek(); // obtiene el valor de chek

private slots:

    // botones correpondientes a las 5 partidas disponibles para el usuario
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    // botones para cargar o sobreescribir partida
    void on_cargar_clicked();

    void on_nuevo_clicked();

private:
    Ui::inicio *ui;
    QGraphicsScene* escena= new QGraphicsScene;
    string alias_Usu_jug;
    int chek;
};

#endif // INICIO_H
