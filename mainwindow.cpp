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
    CanonPausado=0;

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
   powers->start(10000);
   connect(sorteo,SIGNAL(timeout()),this,SLOT(sortear()));
   connect(disparar,SIGNAL(timeout()),this,SLOT(shoot()));

   for(int i=0;i<5;i++){
       canon* c= new canon;
       canones.push_back(c);

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
    delete control;
    delete player1;
    delete player2;
    delete jefe;
    delete animacion;
    delete spawning;
    delete musica;

    delete recto;

}

void MainWindow::BossActive(bool t)
{
    if(t){
        bossOn=true;
        ui->bossHp->setVisible(true);
        jefe->setVida(5000);
        spawning->stop();
        powers->stop();
        scene->addItem(jefe);
        sortear();
        jefe->setPos(260,20);

        sorteo->start(5000);
        disparar->start(1000);
        for(int i=0;i<5;i++){

            canones.at(i)->setPos(250+(i*64),150);
            canones.at(i)->activo=true;
            canones.at(i)->Muerto(false);
            canones.at(i)->vida=2000;
            scene->addItem(canones.at(i));
        }
        setCanones();

    }
    else{
        ui->bossHp->setVisible(false);
        bossOn=false;
        spawning->start(1000-int(puntaje/10));
        powers->start(10000);
        sorteo->stop();
        disparar->stop();
        scene->removeItem(jefe);
        jefe->setPos(1000,1000);
        for(int i=0;i<5;i++){
            canones.at(i)->setPos(1000,1000);
            canones.at(i)->activo=false;
            scene->removeItem(canones.at(i));
        }
    }
}

void MainWindow::spawn()
{
    if(puntaje>100&&puntaje<=500) spawning->start(1200);
    else if(puntaje>500&&puntaje<=1000 ) spawning->start(1000);
    else if(puntaje>1000)spawning->start(1000-int(puntaje/10));
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


}

void MainWindow::esconderGelato()
{
    scene->removeItem(gelato);
    gelato->setRect(0,0,0,0);

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
    disparar->stop();
    sorteo->stop();
    control->encendido(false);
    MenuPausa *men;
    men=new MenuPausa();

    men->setmain(this);
    men->show();

}

void MainWindow::reanudar()
{
    if(!bossOn){
        animacion->start(50);
        spawning->start(1000-(puntaje/10));
        powers->start(5000);
    }
    else{
        disparar->start(1000);
        sorteo->start(5000);
    }

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
    if(bossOn){
        archivo<<jefe->Vida();
        for(int i=0;i<5;i++){ archivo<<";"<<canones.at(i)->vida;}
        archivo<<endl;

    }

}

void MainWindow::cargarDatos(){


    ifstream file(partida);
    char linea[50]="", dato[15]="", dato2[10]="";
    int contador=0, contador2=0;
    file.getline(linea,50);
    if(linea[0]=='1') singlePlayer=true;
    else singlePlayer=false;
    if(linea[2]=='0'){
        bossOn=false;
        ui->bossHp->setVisible(false);
        BossActive(false);
    }
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

    spawning->start(1000-(puntaje/10));

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
        BossActive(true);
        if(puntaje>=1000&&puntaje<1050) jefe->nombre="augusGalactus";
        else if(puntaje>=3500&&puntaje<3550) jefe->nombre="augusGalactus2";
        if(puntaje>=6500&&puntaje<6550) jefe->nombre="augusGalactus";
        setCanones();
        file.getline(linea,50);
        contador=0;
        contador2=0;
        for(int i=0;dato[i]!='\0';i++) dato[i]='\0'; for(int i=0;dato2[i]!='\0';i++) dato2[i]='\0';
        while(linea[contador]!=';'){
            dato[contador]=linea[contador];
            contador++;
        }
        jefe->setVida(atoi(dato));

        for(int i=0;i<5;i++){
            for(int i=0;dato[i]!='\0';i++) dato[i]='\0';
            contador++;
            contador2=0;
            if(i!=4){
                while(linea[contador]!=';'){
                    dato[contador2]=linea[contador];
                    contador++;
                    contador2++;
                }
            }
            else{
                while(linea[contador]!='\0'){
                    dato[contador2]=linea[contador];
                    contador++;
                    contador2++;
                }
            }

            canones.at(i)->vida=atoi(dato);
            if(canones.at(i)->vida<=0) canones.at(i)->Muerto(true);
        }
    }



}

void MainWindow::animar(){
    ui->hp->display(QString::number(player1->Vida()));
    if(!singlePlayer) ui->hp2->display(QString::number(player2->Vida()));
    ui->puntos->display(QString::number(puntaje));
    if(ui->bossHp->isVisible())ui->bossHp->setText(QString::fromStdString(to_string(jefe->Vida())));


    if(!bossOn){
        if(puntaje>=1000&&puntaje<1050){
            jefe->setVillano("augusGalactus");
            BossActive(true);



        }

        else if(puntaje>=3500&&puntaje<3550){
            jefe->setVillano("augusGalactus2");
            BossActive(true);


        }
        else if(puntaje>=6500&&puntaje<6550){
            jefe->setVillano("augusGalactus3");
            BossActive(true);


        }



    }

    if(bossOn&&jefe->Vida()<=0){
        BossActive(false);
        puntaje+=100;
    }

    for(int i=canones.size()-1;i>=0;i--){
        for(int h=balas.size()-1;h>=0;h--){
            if(canones.at(i)->collidesWithItem(balas.at(h))){
                if(canones.at(i)->vida<=0&&canones.at(i)->activo){
                    canones.at(i)->Muerto(true);
                    canones.at(i)->activo=false;
                }
                if(canones.at(i)->activo) canones.at(i)->vida-=balas.at(h)->Efecto();
                scene->removeItem(balas.at(h));
                balas.at(h)->~proyectil();
                balas.removeAt(h);
            }
        }
    }


    for(int i=balasEnemigas.size()-1;i>=0;i--){
        balasEnemigas.at(i)->move();
        if(balasEnemigas.at(i)->collidesWithItem(player1)||balasEnemigas.at(i)->collidesWithItem(player2)){
            if(balasEnemigas.at(i)->collidesWithItem(player1))
            player1->setVida(player1->Vida()-balasEnemigas.at(i)->Efecto());
            if(balasEnemigas.at(i)->collidesWithItem(player2))
                player2->setVida(player2->Vida()-balasEnemigas.at(i)->Efecto());

            scene->removeItem(balasEnemigas.at(i));
            balasEnemigas.at(i)->~proyectil();
            balasEnemigas.removeAt(i);

        }
        else if(balasEnemigas.at(i)->y()>500){
            scene->removeItem(balasEnemigas.at(i));
            balasEnemigas.at(i)->~proyectil();
            balasEnemigas.removeAt(i);
        }
        else{
            for(int h=balas.size()-1;h>=0;h--){
                if(balasEnemigas.at(i)->collidesWithItem(balas.at(h))){
                    scene->removeItem(balasEnemigas.at(i));
                    balasEnemigas.at(i)->~proyectil();
                    balasEnemigas.removeAt(i);

                    scene->removeItem(balas.at(h));
                    balas.at(h)->~proyectil();
                    balas.removeAt(h);
                    break;
                }
            }
        }

    }

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

        }
        else{
            for(int i=drops.size()-1;i>=0;i--){
                if(balas.at(w)->collidesWithItem(drops.at(i))&&drops.at(i)->Efecto()>0){
                    drops.at(i)->setEfecto(drops.at(i)->Efecto()-balas.at(w)->Efecto());
                    scene->removeItem(balas.at(w));
                    balas.at(w)->~proyectil();
                    balas.removeAt(w);
                    puntaje+=5;
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


void MainWindow::shoot()
{
    for(int i=canones.size()-1;i>=0;i--){
        if(canones.at(i)->activo){
            proyectil* p= new proyectil;
            p->setMalo(20);
            p->setPos(canones.at(i)->x()+26,canones.at(i)->y()+31);
            balasEnemigas.push_back(p);
            scene->addItem(p);
            proyectil* h= new proyectil;
            h->setMalo(20);
            h->setPos(canones.at(i)->x()+4,canones.at(i)->y()+31);
            balasEnemigas.push_back(h);
            scene->addItem(h);
            proyectil* j= new proyectil;
            j->setMalo(20);
            j->setPos(canones.at(i)->x()+48,canones.at(i)->y()+31);
            balasEnemigas.push_back(j);
            scene->addItem(j);
        }

    }

}


void MainWindow::sortear(){
    int w= CanonPausado, vmax=0;
    bool muertos=true;
    if(canones.at(CanonPausado)->vida>0)canones.at(CanonPausado)->activo=true;
    for(int i=canones.size()-1;i>=0;i--){
        if(canones.at(i)->vida>0)muertos=false;
        else canones.at(i)->Muerto(true);
        if(canones.at(i)->vida>vmax&&i!=w) {
            CanonPausado=i;
            vmax=canones.at(i)->vida;
        }
    }
    if(CanonPausado!=w)
    canones.at(CanonPausado)->activo=false;
    if(muertos){
        disparar->stop();
        sorteo->stop();

        for(int i=canones.size()-1;i>=0;i--){
            canones.at(i)->Muerto(true);
            canones.at(i)->setPos(1000,1000);
            scene->removeItem(canones.at(i));
        }
    }
}

void MainWindow::setCanones()
{
    if(jefe->Vida()>0){
        if(jefe->nombre=="augusGalactus"){
            for(int i=0;i<5;i++){

                canones.at(i)->setPos(250+(i*64),150);
                canones.at(i)->activo=true;
                canones.at(i)->Muerto(false);
                canones.at(i)->vida=2000;
                scene->addItem(canones.at(i));
            }
        }
        else if(jefe->nombre=="augusGalactus2"){
            for(int i=0;i<5;i++){

                canones.at(i)->setPos(250+(i*64),150);
                canones.at(i)->activo=true;
                canones.at(i)->Muerto(false);
                canones.at(i)->vida=5000;

                canones.at(i)->setPixmap(QPixmap(":/images/bossPeque2.png"));
            }
        }
        else if(jefe->nombre=="augusGalactus3"){
            for(int i=0;i<5;i++){

                canones.at(i)->setPos(250+(i*64),150);
                canones.at(i)->activo=true;
                canones.at(i)->Muerto(false);
                canones.at(i)->vida=7000;

                canones.at(i)->setPixmap(QPixmap(":/images/bossPeque3.png"));
            }
        }
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    control->conectar();
}
