#include "unodos.h"
#include "ui_unodos.h"
#include <string>
#include <iostream>
#include <QDialog>
#include <fstream>
#include "mainwindow.h"



UnoDos::UnoDos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UnoDos)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(escena);
    escena->setSceneRect(0,0,1000,1000);
    escena->setBackgroundBrush(QBrush(QImage(":/images/BG.png")));
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

UnoDos::~UnoDos()
{
    delete ui;
    delete escena;
}

void UnoDos::setalias(string alias)
{
    alias_Usu_jug=alias;
}

void UnoDos::setchek(int _chek){
    chek=_chek;
}



void UnoDos::on_uno_clicked()
{
    string file= alias_Usu_jug+"_"+"Partida"+char(chek+48)+".txt";
    ifstream archivo(file);
    MainWindow *w= new MainWindow;


        ofstream partida(file);
        partida<<"1;0;0\n1000;1;200;411\n";
        partida.close();
        w->show();
        w->setPartida(file);
        w->cargarDatos();

    archivo.close();
    this->close();
}

void UnoDos::on_dos_clicked()
{
    string file= alias_Usu_jug+"_"+"Partida"+char(chek+48)+".txt";
    ifstream archivo(file);
    MainWindow *w= new MainWindow;


        ofstream partida(file);
        partida<<"2;0;0\n1000;1;200;411\n1000;1;300;411";
        partida.close();
        w->show();
        w->setPartida(file);
        w->cargarDatos();
    archivo.close();
    this->close();
}
