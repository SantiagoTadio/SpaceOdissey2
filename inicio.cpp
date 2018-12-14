#include "inicio.h"
#include "ui_inicio.h"
#include "unodos.h"

inicio::inicio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inicio)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(escena);
    escena->setSceneRect(0,0,1000,1000);
    escena->setBackgroundBrush(QBrush(QImage(":/images/BG.png")));
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

inicio::~inicio()
{
    delete ui;
    delete escena;
}

void inicio::setchek(int _chek){
    chek=_chek;
}

int inicio::getchek(){
    return chek;
}

void inicio::cargarDatos(string datos)
{

        char puntaje[10]="", jugadores[2] ="";
        int j=4;
        ifstream archivo(datos);
        ui->cargar->setVisible(true);
        if(archivo.is_open()){
            getline(archivo,datos);

            jugadores[0]=datos[0];
            while(datos[j]!='\0'){
                puntaje[j-4]=datos[j];
                j++;
            }
            if(jugadores[0]=='1') datos= "Puntaje: "+string(puntaje)+"\nUn Jugador";
            else if (jugadores[0]=='2') datos= "Puntaje: "+string(puntaje)+"\nDos Jugadores";


            ui->label->setText(QString::fromStdString(datos));

        }
        else{
            ui->cargar->setVisible(false);
            ui->label->setText(QString::fromStdString("Nueva Partida"));
        }


}

void inicio::on_pushButton_clicked()
{
    string linea = alias_Usu_jug+"_Partida1.txt";
    setchek(1);
    cargarDatos(linea);
}

void inicio::on_pushButton_2_clicked()
{
    string linea = alias_Usu_jug+"_Partida2.txt";
    setchek(2);
    cargarDatos(linea);
}

void inicio::on_pushButton_3_clicked()
{
    string linea = alias_Usu_jug+"_Partida3.txt";
    setchek(3);
    cargarDatos(linea);
}

void inicio::on_pushButton_4_clicked()
{
    string linea = alias_Usu_jug+"_Partida4.txt";
    setchek(4);
    cargarDatos(linea);
}

void inicio::on_pushButton_5_clicked()
{
    string linea = alias_Usu_jug+"_Partida5.txt";
    setchek(5);
    cargarDatos(linea);
}

/*
void inicio::on_pushButton_5_clicked()
{
    string file= alias_Usu_jug+"_"+"Partida"+char(5+48)+".txt";
    ifstream archivo(file);
    MainWindow *w= new MainWindow;
    if(archivo.is_open()){

        w->show();
        w->setPartida(file);
        w->cargarDatos();
    }
    else{
        ofstream partida(file);
        partida<<"2;0;0\n1000;1;200;411\n1000;1;300;411";
        partida.close();
        w->show();
        w->setPartida(file);
        w->cargarDatos();
    }
    archivo.close();
    this->close();
}
*/

void inicio::on_cargar_clicked()
{
    string file= alias_Usu_jug+"_"+"Partida"+char(chek+48)+".txt";
    ifstream archivo(file);
    MainWindow *w= new MainWindow;
    if(archivo.is_open()){

        w->show();
        w->setPartida(file);
        w->cargarDatos();
    }

    archivo.close();
    this->close();
}

void inicio::on_nuevo_clicked()
{
    UnoDos *in;
    in=new UnoDos();
    in->show();
    in->setalias(alias_Usu_jug);
    in->setchek(getchek());
    this->close();
}
