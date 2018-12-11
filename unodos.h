#ifndef UNODOS_H
#define UNODOS_H

#include <string>
#include <iostream>
#include <QDialog>
#include <fstream>
#include "mainwindow.h"

using namespace std;

namespace Ui {
class UnoDos;
}

class UnoDos : public QDialog
{
    Q_OBJECT

public:
    explicit UnoDos(QWidget *parent = nullptr);
    ~UnoDos();
    void setalias(string alias);

    void setchek(int _chek);


private slots:
    void on_uno_clicked();

    void on_dos_clicked();

private:
    Ui::UnoDos *ui;
    string alias_Usu_jug;
    int chek;
};

#endif // UNODOS_H
