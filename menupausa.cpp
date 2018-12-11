#include "menupausa.h"
#include "ui_menupausa.h"

MenuPausa::MenuPausa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuPausa)
{
    ui->setupUi(this);
}

MenuPausa::~MenuPausa()
{
    delete ui;
}

void MenuPausa::on_guardar_clicked()
{
    main->guardarDatos();
}

void MenuPausa::on_partidas_clicked()
{
    main->close();
    inicio *in;
    in=new inicio();
    in->show();
    string p = main->Partida();
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
    main->close();
    registro *re;
    re=new registro();
    re->show();
    this->close();
}

void MenuPausa::on_salir_clicked()
{
    main->close();
    this->close();

}

void MenuPausa::on_reanudar_clicked()
{
    main->reanudar();
    this->close();
}
