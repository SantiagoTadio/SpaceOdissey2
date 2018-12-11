#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menupausa.h"

#define PI 3.14159265359

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    holeOn=false;


   scene = new QGraphicsScene;

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
   connect(powers,SIGNAL(timeout()),this,SLOT(crearPoder()));
   powers->start(5000);




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
    delete control;
    delete player1;
    delete player2;
    delete jefe;
    delete animacion;
    delete spawning;
    delete musica;
    delete varios;
    delete recto;

}

void MainWindow::spawn()
{
    if(puntaje>100&&puntaje<=500) spawning->start(1200);
    else if(puntaje>500&&puntaje<=1000 ) spawning->start(900);
    else if(puntaje>1000)spawning->start(500);
    int px = 90+rand()%631;
    drop * cosa = new drop(true);
    cosa->setPos(px,0);
    scene->addItem(cosa);
    drops.push_back(cosa);
}

void MainWindow::crearPoder(){

    int px = 90+rand()%631;
    drop * cosa = new drop(false);
    cosa->setPos(px,0);
    scene->addItem(cosa);
    pows.push_back(cosa);

}

void MainWindow::esconderRecto()
{
    scene->removeItem(recto);
    recto->setRect(0,0,0,0);
    varios->stop();

}

void MainWindow::esconderGelato()
{
    scene->removeItem(gelato);
    gelato->setRect(0,0,0,0);
    varios->stop();
}

void MainWindow::esconderAgujero()
{
    scene->removeItem(hole);
    hole->setRect(0,0,0,0);
    holeOn=false;
}

void MainWindow::on_pushButton_clicked(){
    pausa();
}

void MainWindow::pausa()
{
    animacion->stop();
    spawning->stop();
    powers->stop();
    musica->stop();
    control->encendido(false);
    MenuPausa *men;
    men=new MenuPausa();
    men->setmain(this);
    men->show();

}

void MainWindow::reanudar()
{
    animacion->start(50);
    spawning->start(1000);
    powers->start(5000);
    control->encendido(true);
    musica->play();
}

void MainWindow::guardarDatos()
{
    ofstream archivo(partida);
    if(singlePlayer) archivo<<"1;";
    else archivo<<"2;";
    if(bossOn)archivo<<"1;";
    else archivo<<"0;";
    archivo<<to_string(puntaje)<<endl;

    archivo<<player1->Vida()<<";"<<player1->Power()<<";"<<player1->x()<<";"<<player1->y()<<endl;
    if(!singlePlayer) archivo<<player2->Vida()<<";"<<player2->Power()<<";"<<player2->x()<<";"<<player2->y()<<endl;
    if(bossOn) archivo<<jefe->Vida()<<";"<<jefe->x()<<";"<<jefe->y()<<endl;
/*
    for(int i= balas.size()-1;i>=0;i--){
        archivo<<"*"<<balas.at(i)->Efecto()<<";"<<balas.at(i)->x()<<";"<<balas.at(i)->y()<<endl;
    }
    for(int i =drops.size()-1;i>=0;i--){
        archivo<<"#"<<drops.at(i)->Type()<<";"<<drops.at(i)->Efecto()<<";"<<drops.at(i)->VelX()<<";"<<drops.at(i)->VelY()<<";"<<drops.at(i)->x()<<";"<<drops.at(i)->y()<<endl;
    }
    */
}

void MainWindow::cargarDatos(){


    ifstream file(partida);
    char linea[50]="", dato[15]="", dato2[10]="";
    int contador=0, contador2=0;
    file.getline(linea,50);
    if(linea[0]=='1') singlePlayer=true;
    else singlePlayer=false;
    if(linea[2]=='0') bossOn=false;
    else bossOn=true;
    for(int i=4;linea[i]!='\0';i++){
        dato[i-4]=linea[i];
    }

    ui->graphicsView->scene()->addItem(player1);

    if(!singlePlayer){
         ui->graphicsView->scene()->addItem(player2);
         control->setMultiplayer(true);
    }

    else{
        ui->label_3->close();
        ui->hp2->close();
    }

    puntaje=atoi(dato);
    for(int i=0;dato[i]!='\0';i++) dato[i]='\0';
    file.getline(linea,50);

    while(linea[contador]!=';'){
        dato[contador]=linea[contador];
        contador++;
    }

    player1->setVida(atoi(dato));
    for(int i=0;dato[i]!='\0';i++) dato[i]='\0';
    dato[0]=linea[contador+1];
    player1->setPoder(atoi(dato));
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
    player1->setPos(atoi(dato),atoi(dato2));
    contador=0;
    contador2=0;
    for(int i=0;dato[i]!='\0';i++) dato[i]='\0'; for(int i=0;dato2[i]!='\0';i++) dato2[i]='\0';

    if(!singlePlayer){
        file.getline(linea,50);

        while(linea[contador]!=';'){
            dato[contador]=linea[contador];
            contador++;
        }
        player2->setVida(atoi(dato));
        for(int i=0;dato[i]!='\0';i++) dato[i]='\0';
        dato[0]=linea[contador+1];
        player2->setPoder(atoi(dato));
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
        player2->setPos(atoi(dato),atoi(dato2));
        contador=0;
        contador2=0;
        for(int i=0;dato[i]!='\0';i++) dato[i]='\0'; for(int i=0;dato2[i]!='\0';i++) dato2[i]='\0';
    }

    if(bossOn){
        file.getline(linea,50);

        while(linea[contador]!=';'){
            dato[contador]=linea[contador];
            contador++;
        }
        jefe->setVida(atoi(dato));
        for(int i=0;dato[i]!='\0';i++) dato[i]='\0';
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
        jefe->setPos(atoi(dato),atoi(dato2));
        contador=0;
        contador2=0;
        for(int i=0;dato[i]!='\0';i++) dato[i]='\0'; for(int i=0;dato2[i]!='\0';i++) dato2[i]='\0';
    }
    /*
    file.getline(linea,50);
    while(file.good()&&linea[0]!='\0'){
        contador=1;
        contador2=0;
        for(int i=0;dato[i]!='\0';i++) dato[i]='\0';  for(int i=0;dato2[i]!='\0';i++) dato2[i]='\0';

        if(linea[0]=='*'){
            proyectil * balita= new proyectil;
            balas.push_back(balita);
            scene->addItem(balita);
            while(linea[contador]!=';'){
                dato[contador-1]=linea[contador];
                contador++;
            }
            contador++;
            balita->setEfecto(atoi(dato));
            for(int i=0;dato[i]!='\0';i++) dato[i]='\0';
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
            balita->setPos(atoi(dato),atoi(dato2));
        }
        else if(linea[0]=='#'){
            drop* cosa= new drop(true);
            drops.push_back(cosa);
            scene->addItem(cosa);
            while(linea[contador]!=';'){
                dato[contador-1]=linea[contador];
                contador++;
            }
            cosa->setType(string(dato));
            for(int i=0;dato[i]!='\0';i++) dato[i]='\0';
            contador++;

            while(linea[contador]!=';'){
                dato[contador2]=linea[contador];
                contador++;
            }
            cosa->setEfecto(atoi(dato));
            for(int i=0;dato[i]!='\0';i++) dato[i]='\0';
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
            cosa->setVel(atof(dato),atof(dato2));
            contador++;
            contador2=0;
            for(int i=0;dato[i]!='\0';i++) dato[i]='\0';  for(int i=0;dato2[i]!='\0';i++) dato2[i]='\0';
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
            cosa->setPos(atoi(dato),atoi(dato2));

        }
        file.getline(linea,50);
    }
    */


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
            if(drops.at(i)->collidesWithItem(recto)){
                drops.at(i)->setVel(drops.at(i)->VelX(),(drops.at(i)->VelY())*(-0.8));
            }
            if(drops.at(i)->collidesWithItem(gelato)){
                float Vcuad, angulo, vy=drops.at(i)->VelY(), vx=drops.at(i)->VelX(), ax, ay;
                int radio, masa;
                if(drops.at(i)->Type()=="asteroideB"){radio=2;masa=100;}
                else if(drops.at(i)->Type()=="asteroideS"){radio=1;masa=30;}
                angulo= atan2(vy,vx);
                Vcuad= (vy*vy)+(vx*vx);
                ax= -(10*Vcuad*(radio*radio)*cos(angulo))/masa;
                ay= -(10*Vcuad*(radio*radio)*sin(angulo))/masa;

                drops.at(i)->setVel(drops.at(i)->VelX()+(ax*0.1),drops.at(i)->VelY()+(ay*0.1));
            }

            if(holeOn) drops.at(i)->move(1,hole->x(),hole->y());
            else{
                if(singlePlayer) drops.at(i)->move(1,player1->x(),player1->y());
                else drops.at(i)->move(1,player1->x(),player1->y(),player2->x(),player2->y());
            }

            if(drops.at(i)->collidesWithItem(player1)||drops.at(i)->collidesWithItem(player2)){
                if(drops.at(i)->collidesWithItem(player1))
                player1->setVida(player1->Vida()-drops.at(i)->Efecto());
                if(drops.at(i)->collidesWithItem(player2))
                    player2->setVida(player2->Vida()-drops.at(i)->Efecto());

                scene->removeItem(drops.at(i));
                drops.at(i)->~drop();
                drops.removeAt(i);

            }
            else if(drops.at(i)->y()>500){
                scene->removeItem(drops.at(i));
                drops.at(i)->~drop();
                drops.removeAt(i);
                player1->setVida(player1->Vida()-drops.at(i)->Efecto());
                if(!singlePlayer) player2->setVida(player2->Vida()-drops.at(i)->Efecto());
            }
            else if(drops.at(i)->collidesWithItem(hole)){
                scene->removeItem(drops.at(i));
                drops.at(i)->~drop();
                drops.removeAt(i);
            }

        }
        else{
            scene->removeItem(drops.at(i));
            drops.at(i)->~drop();
            drops.removeAt(i);
        }

    }
    for(int i=pows.size()-1;i>=0;i--){
        pows.at(i)->move();
        if(pows.at(i)->collidesWithItem(player2)||pows.at(i)->collidesWithItem(player1)){

            if(pows.at(i)->Type()=="cura"){
                if(pows.at(i)->collidesWithItem(player1)) player1->setVida(player1->VidaMax());
                if(pows.at(i)->collidesWithItem(player2)) player2->setVida(player2->VidaMax());
            }
            else if(pows.at(i)->Type()=="veneno"){
                if(pows.at(i)->collidesWithItem(player1)) player1->setVida(1);
                if(pows.at(i)->collidesWithItem(player2)) player2->setVida(1);
            }
            else if(pows.at(i)->Type()=="mejora"){
                if(pows.at(i)->collidesWithItem(player1)) player1->setPoder(player1->Power()+1);
                if(pows.at(i)->collidesWithItem(player2)) player2->setPoder(player2->Power()+1);
            }
            else if(pows.at(i)->Type()=="escudo"){
                 recto->setRect(0,0,720,30);
                 recto->setBrush(Qt::green);
                 recto->setPos(50,300);
                 scene->addItem(recto);
                 QTimer::singleShot(10000,this,SLOT(esconderRecto()));
            }
            else if(pows.at(i)->Type()=="gelato"){
                gelato->setRect(0,0,720,150);
                gelato->setBrush(Qt::blue);
                gelato->setPos(50,150);
                scene->addItem(gelato);
                QTimer::singleShot(10000,this,SLOT(esconderGelato()));
            }
            else if(pows.at(i)->Type()=="agujero"){
                hole->setRect(0,0,50,50);
                hole->setBrush(Qt::black);
                hole->setPos(380,225);
                scene->addItem(hole);
                holeOn=true;
                QTimer::singleShot(10000,this,SLOT(esconderAgujero()));

            }




            scene->removeItem(pows.at(i));
            pows.at(i)->~drop();
            pows.removeAt(i);

        }
        else if(pows.at(i)->y()>500){
            scene->removeItem(pows.at(i));
            pows.at(i)->~drop();
            pows.removeAt(i);

        }

    }

}



