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
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MenuPausa::~MenuPausa()
{
    delete ui;
    delete mai;
    delete escena;
}

void MenuPausa::esconder()
{
    ui->guardar->setVisible(false);
    ui->reanudar->setVisible(false);
}

void MenuPausa::on_guardar_clicked()
{
    mai->guardarDatos();
}

void MenuPausa::on_partidas_clicked()
{
    mai->close();
    inicio *in;
    in=new inicio();
    in->show();
    string p = mai->Partida();
    char usu[20]="";
    for(int i=0;p[i]!='_';i++){
        usu[i]=p[i];
    }
    in->setUsuario(string(usu));
    in->setchek(1);
    string linea = string(usu)+"_Partida1.txt";
    in->cargarDatos(linea);
    this->close();
}

void MenuPausa::on_inicio_clicked()
{
    mai->close();
    registro *re;
    re=new registro();
    re->show();
    this->close();
}

void MenuPausa::on_salir_clicked()
{
    mai->close();
    this->close();

}

void MenuPausa::on_reanudar_clicked()
{
    mai->reanudar();
    this->close();
}
