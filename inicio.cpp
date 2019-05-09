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
    escena->setBackgroundBrush(QBrush(QImage(":/images/BG.png"))); // al dialogo se le pone una imagen de fondo
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

inicio::~inicio() // destructor
{
    delete ui;
    delete escena;
}

void inicio::setchek(int _chek){ // se le asigna la partida en donde va a jugar
    chek=_chek;
}

int inicio::getchek(){ // Retorna la partida donde esta jugando
    return chek;
}

void inicio::cargarDatos(string datos)
{

        char puntaje[10]="", jugadores[2] ="";
        int j=4;
        ifstream archivo(datos);
        ui->cargar->setVisible(true); // Vuelve visible el boton cargar
        if(archivo.is_open()){ // si el archivo se puede abrir( es porque hay una partida guardada)
            getline(archivo,datos);

            jugadores[0]=datos[0];
            while(datos[j]!='\0'){
                puntaje[j-4]=datos[j];
                j++;
            }
            if(jugadores[0]=='1') datos= "Puntaje: "+string(puntaje)+"\nUn Jugador";  // si es un jugador
            else if (jugadores[0]=='2') datos= "Puntaje: "+string(puntaje)+"\nDos Jugadores"; // si son dos jugadores


            ui->label->setText(QString::fromStdString(datos)); // muestra en el dialogo el puntaje de la partida y si es de un jugador o dos

        }
        else{
            ui->cargar->setVisible(false); // Vuelve invisible el boton cargar
            ui->label->setText(QString::fromStdString("Nueva Partida")); // muestra en el dialogo "Nueva Partida"
        }


}

void inicio::on_pushButton_clicked()
{
    string linea = alias_Usu_jug+"_Partida1.txt";
    setchek(1); // se le asigna la partida clickeada
    cargarDatos(linea); // mira si hay una parida guardada
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
    string file= alias_Usu_jug+"_"+"Partida"+char(chek+48)+".txt"; // nombre del archivo de texto donde se guarda la partida
    ifstream archivo(file);
    MainWindow *w= new MainWindow;
    if(archivo.is_open()){

        w->show(); // abre el dialogo
        w->setPartida(file); // se asigna el nombre del archivo de texto
        w->cargarDatos(); // se cargan los datos de la partida
    }

    archivo.close();
    this->close(); // cierra el dialogo
}

void inicio::on_nuevo_clicked()
{
    UnoDos *in;
    in=new UnoDos();
    in->show(); // abre el dialogo
    in->setalias(alias_Usu_jug); // se asigna el alias del usuario que inicio sesion
    in->setchek(getchek());
    this->close();
}
