#ifndef REGISTRO_H
#define REGISTRO_H

#include <QDialog>
#include <QList>
#include "usuario.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <QGraphicsScene>

using namespace std;

namespace Ui {
class registro;
}

class registro : public QDialog // pagina de ingreso y registro de usuario
{
    Q_OBJECT

public:
    explicit registro(QWidget *parent = nullptr);
    ~registro();
    //void setTxt();
    bool veriUs(string _alias,string _pass); // verifica la existencia de un usuario en la base de datos
    void llenarList(); // lectura de datos de usuarios para llenar la lista listUs
    void guardarArch(); // se guarda el alias y la clave en el archivo de texto





private slots:
    void on_pushButton_clicked(); // Registra al usuario si cumple las condiciones

    void on_pushButton_2_clicked(); // Inicia sesion si cumple los requerimientos

private:
    Ui::registro *ui;
    QGraphicsScene* escena= new QGraphicsScene;
    QList<usuario> listUs;

};

#endif // REGISTRO_H

