#include "registro.h"
#include "inicio.h"
#include "ui_registro.h"

registro::registro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registro)
{
    ui->setupUi(this);

    llenarList();
}

registro::~registro()
{
    delete ui;
}

bool registro::veriUs(string _alias, string _pass)
{
    int n=listUs.size();
    for(int i=0;i<n;i++){
        //cout<<listUs[i].get_alias()<<","<<listUs[i].get_pass()<<","<<endl;
        if(listUs[i].get_alias() == _alias && listUs[i].get_pass()==_pass){
            return true;
        }

    }
    return false;
}

void registro::llenarList()
{

    string line;
    char nombreRouter[100]={};
    char costo[100]={};
    int i=0,j=0;


    ifstream myfile ("datosUs.txt");
    if (myfile.is_open()){

        while (myfile.good()){

            getline (myfile,line);


            while(line[i]!=','){
                nombreRouter[j]=line[i];
                j++;
                i++;
            }

            i++;
            j=0;
            while(line[i]!=';'){
                costo[j]=line[i];
                i++;
                j++;
            }

            usuario us(nombreRouter,costo);
            listUs.push_back(us);


            j=0;
            i=0;
            for(int w=0; nombreRouter[w]!='\0';w++)nombreRouter[w]='\0';

            for(int w=0; costo[w]!='\0';w++)costo[w]='\0';


        }
        myfile.close();
    }
    else{
        cout<<"no se pudo abrir el archivo";
    }


}

void registro::guardarArch()
{
    ofstream myfileA("datosUs.txt");
    for(int i=0;i<listUs.size();i++ ){
        myfileA<<listUs[i].get_alias()<<","<<listUs[i].get_pass()<<";";
        if(i!=listUs.size()-1) myfileA<<endl;
    }
    myfileA.close();
}



void registro::on_pushButton_clicked()
{
    QString alias,pass,password;
    alias=ui->lineEdit->text();
    pass=ui->lineEdit_4->text();
    password=ui->lineEdit_5->text();

    if(!alias.isDetached() && !pass.isEmpty() && !password.isEmpty()){
        bool cond=false;
        for(int i=0;i<listUs.size();i++){
            if(listUs[i].get_alias()==alias.toStdString()){
                cond=true;
                break;
            }
        }
        if(cond==true){
            cout<<"usuario ya creado"<<endl;
        }
        else{

                if(pass==password){
                    usuario us(alias.toStdString(),pass.toStdString());
                    listUs.push_back(us);
                    guardarArch();


                }
                else{
                    cout<<"Las claves no considen"<<endl;
                }
        }


    }
    else{
        cout<<"Esta vacio"<<endl;
    }

}

void registro::on_pushButton_2_clicked()
{
    QString alias,pass;
    alias=ui->lineEdit_2->text();
    pass=ui->lineEdit_3->text();



    if(!alias.isDetached() && !pass.isEmpty()){
        bool cond=veriUs(alias.toStdString(),pass.toStdString());
        if(cond){
            inicio *in;
            in=new inicio();
            in->show();
            in->setUsuario(alias.toStdString());
            string linea = alias.toStdString()+"_Partida1.txt";
            in->setchek(1);
            in->cargarDatos(linea);
            this->close();

        }
        else{
            cout<<"se equivoco verifique"<<endl;
        }
    }
    else{
        cout<<"Esta vacio"<<endl;
    }
}




/*

fstream myfile;
        myfile.open("datosUs.txt");

myfile<<_alias<<","<<_pass<<";\n";
myfile.close();
*/
