#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    singlePlayer=false;
    bossOn=false;

   scene = new QGraphicsScene;
   QMediaPlayer * musica = new QMediaPlayer;
   musica->setMedia(QUrl("qrc:/music/audio.mp3"));
   scene->setSceneRect(0,0,821,501);
   scene->setBackgroundBrush(QBrush(QImage(":/images/bg2.png")));
   ui->graphicsView->setScene(scene);
   ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

   connect(animacion,SIGNAL(timeout()),this,SLOT(animar()));
   animacion->start(50);
   connect(spawning,SIGNAL(timeout()),this,SLOT(spawn()));
   spawning->start(1500);

   player1->setPos(385,411);

   player2->setPos(385,411);
   ui->graphicsView->scene()->addItem(player1);
   if(!singlePlayer)
   ui->graphicsView->scene()->addItem(player2);
   else{
       ui->label_3->close();
       ui->hp2->close();
   }


   control->pj1=player1;
   control->pj2=player2;
   scene->addItem(control);

   control->setFlag(QGraphicsItem::ItemIsFocusable);
   control->setFocus();

   musica->play();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::on_plainTextEdit_windowIconTextChanged(const QString &iconText)
{
    scene->setBackgroundBrush(QBrush(QImage(":/images/BG.png")));
}

void MainWindow::spawn()
{
    if(puntaje==100) spawning->start(1200);
    else if(puntaje==500 ) spawning->start(900);
    else if(puntaje==1000)spawning->start(500);
    int px = 90+rand()%631;
    drop * cosa = new drop(true);
    cosa->setPos(px,0);
    scene->addItem(cosa);
    drops.push_back(cosa);
}

void MainWindow::on_pushButton_clicked(){
    pausa();
}

void MainWindow::pausa()
{
    animacion->stop();
    spawning->stop();
    control->encendido(false);
    guardarDatos();
}

void MainWindow::reanudar()
{
    animacion->start(50);
    spawning->start(1000);
    control->encendido(true);
}

void MainWindow::guardarDatos()
{
    ofstream archivo("datos.txt");
    if(singlePlayer) archivo<<"1;";
    else archivo<<"2;";
    if(bossOn)archivo<<"1;";
    else archivo<<"0;";
    archivo<<to_string(puntaje)<<endl;

    archivo<<player1->Vida()<<";"<<player1->Power()<<";"<<player1->x()<<";"<<player1->y()<<endl;
    if(!singlePlayer) archivo<<player2->Vida()<<";"<<player2->Power()<<";"<<player2->x()<<";"<<player2->y()<<endl;
    if(bossOn) archivo<<jefe->Vida()<<";"<<jefe->x()<<";"<<jefe->y()<<endl;

    for(int i= balas.size()-1;i>=0;i--){
        archivo<<"*"<<balas.at(i)->Efecto()<<";"<<balas.at(i)->x()<<";"<<balas.at(i)->y()<<endl;
    }
    for(int i =drops.size()-1;i>=0;i--){
        archivo<<"#"<<drops.at(i)->Type()<<";"<<drops.at(i)->Efecto()<<";"<<drops.at(i)->VelX()<<";"<<drops.at(i)->VelY()<<";"<<drops.at(i)->x()<<";"<<drops.at(i)->y()<<endl;
    }
}

void MainWindow::cargarDatos(string archivo){
    ifstream file(archivo);
    string linea="", dato="", dato2="";
    int contador=0, contador2=0;
    getline(file,linea);
    if(linea[0]=='1') singlePlayer= true;
    else singlePlayer=false;
    if(linea[2]=='0') bossOn=false;
    else bossOn=true;
    for(int i=4;linea[i]!='\0';i++)dato[i-4]=linea[i];
    puntaje= stoi(dato);
    dato="";
    getline(file,linea);

    while(linea[contador]!=';'){
        dato[contador]=linea[contador];
        contador++;
    }
    player1->setVida(stoi(dato));
    dato=linea[contador+1];
    player1->setPoder(stoi(dato));
    contador+=3;

    while(linea[contador]!=';'){
        dato[contador2]=linea[contador];
        contador++;  contador2++;
    }
    contador2=0;
    contador++;
    while(linea[contador]!='\0'){
        dato2[contador2]=linea[contador];
        contador++;  contador2++;
    }
    player1->setPos(stoi(dato),stoi(dato2));
    contador=0;
    contador2=0;
    dato=""; dato2="";

    if(!singlePlayer){
        getline(file,linea);

        while(linea[contador]!=';'){
            dato[contador]=linea[contador];
            contador++;
        }
        player2->setVida(stoi(dato));
        dato=linea[contador+1];
        player2->setPoder(stoi(dato));
        contador+=3;

        while(linea[contador]!=';'){
            dato[contador2]=linea[contador];
            contador++;  contador2++;
        }
        contador2=0;
        contador++;
        while(linea[contador]!='\0'){
            dato2[contador2]=linea[contador];
            contador++;  contador2++;
        }
        player2->setPos(stoi(dato),stoi(dato2));
        contador=0;
        contador2=0;
        dato=""; dato2="";
    }

    if(bossOn){
        getline(file,linea);

        while(linea[contador]!=';'){
            dato[contador]=linea[contador];
            contador++;
        }
        jefe->setVida(stoi(dato));
        dato="";
        contador++;

        while(linea[contador]!=';'){
            dato[contador2]=linea[contador];
            contador++;  contador2++;
        }
        contador2=0;
        contador++;
        while(linea[contador]!='\0'){
            dato2[contador2]=linea[contador];
            contador++;  contador2++;
        }
        jefe->setPos(stoi(dato),stoi(dato2));
        contador=0;
        contador2=0;
        dato=""; dato2="";
    }

    while(file.good()){
        contador=1;
        contador2=0;
        dato="";  dato2="";
        getline(file,linea);
        if(linea[0]=='*'){
            proyectil* balita = new proyectil;
            balas.push_back(balita);
            while(linea[contador]!=';'){
                dato[contador-1]=linea[contador];
                contador++;
            }
            contador++;
            balita->setEfecto(stoi(dato));
            dato="";
            while(linea[contador]!=';'){
                dato[contador2]=linea[contador];
                contador++; contador2++;
            }
            contador++;
            contador2=0;
            while(linea[contador]!='\0'){
                dato2[contador2]=linea[contador];
                contador++;  contador2++;
            }
            balita->setPos(stoi(dato),stoi(dato2));
        }
        else if(linea[0]=='#'){
            drop * cosa = new drop(true);
            drops.push_back(cosa);
            while(linea[contador]!=';'){
                dato[contador-1]=linea[contador];
                contador++;
            }
            cosa->setType(dato);
            dato="";
            contador++;

            while(linea[contador]!=';'){
                dato[contador2]=linea[contador];
                contador++;
            }
            cosa->setEfecto(stoi(dato));
            dato="";
            contador++;
            contador2=0;

            while(linea[contador]!=';'){
                dato[contador2]=linea[contador];
                contador++;
            }
            contador++;
            contador2=0;
            while(linea[contador]!=';'){
                dato2[contador2]=linea[contador];
                contador++;
            }
            cosa->setVel(stof(dato),stof(dato2));
            contador++;
            contador2=0;
            dato=""; dato2="";
            //&&&&&&&&&&&&&6

            while(linea[contador]!=';'){
                dato[contador2]=linea[contador];
                contador++;
            }
            contador++;
            contador2=0;
            while(linea[contador]!='\0'){
                dato2[contador2]=linea[contador];
                contador++;
            }
            cosa->setPos(stoi(dato),stoi(dato2));

        }
    }





}



void MainWindow::animar(){
    ui->hp->display(QString::number(player1->Vida()));
    if(!singlePlayer) ui->hp2->display(QString::number(player2->Vida()));
    ui->puntos->display(QString::number(puntaje));
    for(int w=balas.size()-1;w>=0;w--){
        balas.at(w)->move();
        if(balas.at(w)->collidesWithItem(jefe)){
            jefe->setVida(jefe->Vida()-balas.at(w)->Efecto());
            scene->removeItem(balas.at(w));
            balas.at(w)->~proyectil();
            balas.removeAt(w);
        }
        else if (balas.at(w)->y()<=0) {
            scene->removeItem(balas.at(w));
            balas.at(w)->~proyectil();
            balas.removeAt(w);
            puntaje-=1;
        }
        else{
            for(int i=drops.size()-1;i>=0;i--){
                if(balas.at(w)->collidesWithItem(drops.at(i))&&drops.at(i)->Efecto()>0){
                    drops.at(i)->setEfecto(drops.at(i)->Efecto()-balas.at(w)->Efecto());
                    scene->removeItem(balas.at(w));
                    balas.at(w)->~proyectil();
                    balas.removeAt(w);
                    puntaje+=10;
                    break;
                }
            }
        }
    }

    for(int i=drops.size()-1;i>=0;i--){
        if(drops.at(i)->Efecto()>0){
            drops.at(i)->move(1,player1->x(),player1->y(),player2->x(),player2->y());
            if(drops.at(i)->collidesWithItem(player1)||drops.at(i)->collidesWithItem(player2)){
                if(drops.at(i)->collidesWithItem(player1))
                player1->setVida(player1->Vida()-drops.at(i)->Efecto());
                if(drops.at(i)->collidesWithItem(player2)){
                    player2->setVida(player2->Vida()-drops.at(i)->Efecto());
                scene->removeItem(drops.at(i));
                drops.at(i)->~drop();
                drops.removeAt(i);
                }
            }
            else if(drops.at(i)->y()>500){
                scene->removeItem(drops.at(i));
                drops.at(i)->~drop();
                drops.removeAt(i);
                player1->setVida(player1->Vida()-drops.at(i)->Efecto());
                if(!singlePlayer) player2->setVida(player2->Vida()-drops.at(i)->Efecto());
            }

        }
        else{
            scene->removeItem(drops.at(i));
            drops.at(i)->~drop();
            drops.removeAt(i);
        }

    }
}

void MainWindow::on_pushButton_2_clicked()
{
    reanudar();
}
