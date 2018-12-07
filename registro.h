#ifndef REGISTRO_H
#define REGISTRO_H

#include <QDialog>
#include <QList>
#include "usuario.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

namespace Ui {
class registro;
}

class registro : public QDialog
{
    Q_OBJECT

public:
    explicit registro(QWidget *parent = nullptr);
    ~registro();
    void setTxt();
    bool veriUs(string _alias,string _pass);
    void llenarList();
    void guardarArch();





private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::registro *ui;
    QList<usuario> listUs;

};

#endif // REGISTRO_H

