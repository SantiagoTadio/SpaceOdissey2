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
    ui->graphicsView->setScene(escena); //crea la escena
    escena->setSceneRect(0,0,1000,1000);
    escena->setBackgroundBrush(QBrush(QImage(":/images/BG.png"))); //fondo de la escena
    //desactiva scrollbars horizontal y vertical
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
    alias_Usu_jug=alias; //asigna el nombre de usuario
}

void UnoDos::setchek(int _chek){
    chek=_chek; //asigna el numero de la opción elegida(chek)
}



void UnoDos::on_uno_clicked()
{
    //si selecciona un jugador
    string file= alias_Usu_jug+"_"+"Partida"+char(chek+48)+".txt";//crea el nombre del archivo de texto que almacenará la partida
    ifstream archivo(file);//abre archivo
    MainWindow *w= new MainWindow;


        ofstream partida(file);
        partida<<"1;0;0\n1000;1;200;411\n"; //ingresa datos iniciales de partida para un jugador
        partida.close();
        w->show();//abre mainwindow
        w->setPartida(file); //asigna la partida al mainwindow
        w->cargarDatos(); //carga los datos del archivo creado

    archivo.close();
    this->close(); //cierra unodos
}

void UnoDos::on_dos_clicked()
{
    //si selecciona dos jugadores
    string file= alias_Usu_jug+"_"+"Partida"+char(chek+48)+".txt";//crea el nombre del archivo de texto que almacenará la partida
    ifstream archivo(file);//abre archivo
    MainWindow *w= new MainWindow;


        ofstream partida(file);//abre archivo
        partida<<"2;0;0\n1000;1;200;411\n1000;1;300;411"; //ingresa datos iniciales de partida para dos jugadores
        partida.close();
        w->show();//abre mainwindow
        w->setPartida(file); //asigna la partida al mainwindow
        w->cargarDatos(); //carga los datos del archivo creado
    archivo.close();
    this->close(); //cierra unodos
}
