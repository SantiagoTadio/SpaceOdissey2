#include "inicio.h"
#include "ui_inicio.h"

inicio::inicio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inicio)
{
    ui->setupUi(this);

}

inicio::~inicio()
{
    delete ui;
}

void inicio::cargarDatos()
{
    for(int i=1;i<=5;i++){
        string file= alias_Usu_jug+"_"+"Partida"+char(i+48)+".txt";
        char puntaje[10]="", jugadores[2] ="";
        int j=4;
        ifstream archivo(file);
        cout<<file;
        if(archivo.is_open()){
            getline(archivo,file);

            jugadores[0]=file[0];
            while(file[j]!='\0'){
                puntaje[j-4]=file[j];
                j++;
            }
            file= "Puntaje: "+string(puntaje)+'\n'+"Numero de Jugadores: "+string(jugadores);

            if(i==1) ui->label->setText(QString::fromStdString(file));
            if(i==2) ui->label_2->setText(QString::fromStdString(file));
            if(i==3) ui->label_3->setText(QString::fromStdString(file));
            if(i==4) ui->label_4->setText(QString::fromStdString(file));
            if(i==5) ui->label_5->setText(QString::fromStdString(file));


        }
        else{
            if(i==1) ui->label->setText(QString::fromStdString("No hay partida guardada"));
            if(i==2) ui->label_2->setText(QString::fromStdString("No hay partida guardada"));
            if(i==3) ui->label_3->setText(QString::fromStdString("No hay partida guardada"));
            if(i==4) ui->label_4->setText(QString::fromStdString("No hay partida guardada"));
            if(i==5) ui->label_5->setText(QString::fromStdString("No hay partida guardada"));
        }

    }
}

void inicio::on_pushButton_clicked()
{

    string file= alias_Usu_jug+"_"+"Partida"+char(1+48)+".txt";
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

void inicio::on_pushButton_2_clicked()
{
    string file= alias_Usu_jug+"_"+"Partida"+char(2+48)+".txt";
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

void inicio::on_pushButton_3_clicked()
{
    string file= alias_Usu_jug+"_"+"Partida"+char(3+48)+".txt";
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

void inicio::on_pushButton_4_clicked()
{
    string file= alias_Usu_jug+"_"+"Partida"+char(4+48)+".txt";
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
