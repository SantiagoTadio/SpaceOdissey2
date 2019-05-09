#include "registro.h"
#include "inicio.h"
#include "ui_registro.h"

registro::registro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registro)
{
    ui->setupUi(this);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);//crea cuadros de contraseña
    ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    ui->lineEdit_5->setEchoMode(QLineEdit::Password);
    llenarList(); //llena la lista de usuarios

    ui->graphicsView->setScene(escena);
    escena->setSceneRect(0,0,1000,1000);
    escena->setBackgroundBrush(QBrush(QImage(":/images/BG.png")));//fondo
    //desactiva scrollbars horizonal y vertical
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->msj_ins->setVisible(false);
    ui->msj_reg->setVisible(false);
}

registro::~registro()
{
    delete ui;
    delete escena;
}


bool registro::veriUs(string _alias, string _pass)
{
    int n=listUs.size();
    for(int i=0;i<n;i++){//recorre la lista de usuarios

        if(listUs[i].get_alias() == _alias && listUs[i].get_pass()==_pass){ //verifica que coincidan el nombre de usuario y la contraseña
            return true;
        }

    }
    return false;
}

void registro::llenarList()
{

    string line;
    char alias[100]={};
    char clave[100]={};
    int i=0,j=0;


    ifstream myfile ("datosUs.txt");//abre el archivo de texto que contiene los alias y sus respectivas contraseñas
    if (myfile.is_open()){

        while (myfile.good()){//lee el archivo

            getline (myfile,line);//lee una linea


            while(line[i]!=','){
                alias[j]=line[i]; //llena el nombre de usuario
                j++;
                i++;
            }

            i++;
            j=0;
            while(line[i]!=';'){
                clave[j]=line[i];//llena la contraseña
                i++;
                j++;
            }

            usuario us(alias,clave); //crea un objeto tipo usuario
            listUs.push_back(us);//añade el usuario a una lista de usuarios


            j=0;
            i=0;
            //vacia los char[] de usuario y clave
            for(int w=0; alias[w]!='\0';w++)alias[w]='\0';

            for(int w=0; clave[w]!='\0';w++)clave[w]='\0';


        }
        myfile.close();//cierra el archivo
    }
    else{
        cout<<"no se pudo abrir el archivo";
    }


}

void registro::guardarArch()
{
    ofstream myfileA("datosUs.txt"); //abre archivo de usuarios
    for(int i=0;i<listUs.size();i++ ){
        myfileA<<listUs[i].get_alias()<<","<<listUs[i].get_pass()<<";"; //en cada linea escribe el nombre usuario seguido por ",", la contraseña y separados un usuario de otro por ";"
        if(i!=listUs.size()-1) myfileA<<endl;
    }
    myfileA.close();//cierra archivo
}



void registro::on_pushButton_clicked()
{
    QString alias,pass,password;
    //obtiene los valores ingresados en los line Edit
    alias=ui->lineEdit->text();
    pass=ui->lineEdit_4->text();
    password=ui->lineEdit_5->text();

    if(!alias.isDetached() && !pass.isEmpty() && !password.isEmpty()){ //si todas las casillas tienen información
        bool cond=false;
        for(int i=0;i<listUs.size();i++){
            if(listUs[i].get_alias()==alias.toStdString()){ //verifica si el usuario ingresado existe
                cond=true;
                break;
            }
        }
        if(cond==true){
            cout<<"usuario ya creado"<<endl;
            ui->msj_reg->setVisible(true);
            ui->msj_reg->setText(QString::fromStdString("El nombre de usuario no está disponible"));
        }
        else{

                if(pass==password){ //si la contraseña y la repeticion de contraseña coinciden
                    usuario us(alias.toStdString(),pass.toStdString()); //crea un nuevo usuario con los datos ingresados
                    listUs.push_back(us);
                    guardarArch();


                }
                else{ //de lo contrario
                    cout<<"Las claves no conciden"<<endl;
                    ui->msj_reg->setVisible(true);
                    ui->msj_reg->setText(QString::fromStdString("Las claves no coinciden"));
                }
        }


    }
    else{//si falta algo por llenar
        cout<<"Esta vacio"<<endl;
        ui->msj_reg->setVisible(true);
        ui->msj_reg->setText(QString::fromStdString("Debe rellenar todas las casillas"));
    }

}

void registro::on_pushButton_2_clicked()
{
    QString alias,pass;
    //obtiene lo ingresado en los line Edit
    alias=ui->lineEdit_2->text();
    pass=ui->lineEdit_3->text();



    if(!alias.isDetached() && !pass.isEmpty()){ //si ambas casillas tienen información
        bool cond=veriUs(alias.toStdString(),pass.toStdString()); //verifica que el usuario y contraseña coincidan con los de la base de datos
        if(cond){ //si coinciden
            inicio *in;
            in=new inicio();
            in->show();//se lleva a la pagina de inicio
            in->setUsuario(alias.toStdString()); //pasa el usuario
            string linea = alias.toStdString()+"_Partida1.txt"; //crea el nombre de partida
            in->setchek(1); //casilla seleccionada por defecto
            in->cargarDatos(linea); //carga datos del archivo de texto con el nombre de partida creado
            this->close();

        }
        else{ //si el usuario y contraseña no coinciden
            cout<<"se equivocó, verifique"<<endl;
            ui->msj_ins->setVisible(true);
            ui->msj_ins->setText(QString::fromStdString("Nombre de usuario o contraseña errados"));
        }
    }
    else{//si faltan casillas por llenar
        cout<<"Esta vacio"<<endl;
        ui->msj_ins->setVisible(true);
        ui->msj_ins->setText(QString::fromStdString("Debe llenar todas las casillas"));
    }
}



