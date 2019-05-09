#include "menupausa.h"
#include "ui_menupausa.h"

MenuPausa::MenuPausa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuPausa)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(escena);
    escena->setSceneRect(0,0,1000,1000);
    escena->setBackgroundBrush(QBrush(QImage(":/images/BG.png")));
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//desactiva el scrollbar horizontal
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//desactiva el scrollbar vertical
}

MenuPausa::~MenuPausa()
{
    delete ui;
    delete mai;
    delete escena;
}

void MenuPausa::esconder()
{
    ui->guardar->setVisible(false);//vuelve invisible el boton guardar
    ui->reanudar->setVisible(false);//vuelve invisible el boton reanudar
}

void MenuPausa::on_guardar_clicked()
{
    mai->guardarDatos();//llama la funcion guardar datos del mainwindow
}

void MenuPausa::on_partidas_clicked()
{
    mai->close();//cierra el mainwindow
    inicio *in;
    in=new inicio();
    in->show();//abre el inicio
    string p = mai->Partida();
    char usu[20]="";
    for(int i=0;p[i]!='_';i++){
        usu[i]=p[i];//consigue el alias
    }
    in->setUsuario(string(usu));//asigna el ususario
    in->setchek(1);//partida seleccionada por defecto
    string linea = string(usu)+"_Partida1.txt";
    in->cargarDatos(linea);//carga datos de un archivo de texto
    this->close();//cierra el menu pausa
}

void MenuPausa::on_inicio_clicked()
{
    mai->close();//cierra mainwindow
    registro *re;
    re=new registro();
    re->show(); //abre ventana de registro
    this->close(); //cierra el menu pausa
}

void MenuPausa::on_salir_clicked()
{
    mai->close(); //cierra mainwindow
    this->close(); // cierra menu pausa

}

void MenuPausa::on_reanudar_clicked()
{
    mai->reanudar(); //reinicia el juego en mainwindow
    this->close(); //cierra el menu pausa
}
