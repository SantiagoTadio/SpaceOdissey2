#ifndef INICIO_H
#define INICIO_H
#include <string>
#include <iostream>
#include <QDialog>
#include <fstream>
#include "mainwindow.h"

using namespace std;
namespace Ui {
class inicio;
}

class inicio : public QDialog
{
    Q_OBJECT

public:
    explicit inicio(QWidget *parent = nullptr);
    void setUsuario(string u){alias_Usu_jug=u;}
    ~inicio();
    void cargarDatos();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::inicio *ui;
    string alias_Usu_jug;
};

#endif // INICIO_H
