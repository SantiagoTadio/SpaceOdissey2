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

   musica->setMedia(QUrl("qrc:/music/audio.mp3")); //música de fondo
   scene->setSceneRect(0,0,821,501);
   scene->setBackgroundBrush(QBrush(QImage(":/images/bg2.png"))); //fondo de pantalla
   ui->graphicsView->setScene(scene);
   //desactiva la scroll bar horizontal y vertical
   ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

   //conexión de timers
   connect(animacion,SIGNAL(timeout()),this,SLOT(animar()));
   animacion->start(50); // activa la función principal la animación
   connect(spawning,SIGNAL(timeout()),this,SLOT(spawn()));
   spawning->start(1500);//activa la aparición de los asteroides
   connect(powers,SIGNAL(timeout()),this,SLOT(crearPoder()));
   powers->start(5000);//activa la aparición de poderes
   connect(sorteo,SIGNAL(timeout()),this,SLOT(sortear()));
   connect(disparar,SIGNAL(timeout()),this,SLOT(shoot()));

   for(int i=0;i<5;i++){ //crea los cañones del jefe, pero no los añade a la escena
       canon* c= new canon;
       canones.push_back(c);

   }


   control->pj1=player1; // crea los jugadores y el controlador
   control->pj2=player2;
   scene->addItem(control);

   control->setFlag(QGraphicsItem::ItemIsFocusable);
   control->setFocus();// hace que control reciba las señales del teclado




   musica->play(); //reproduce la música

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
    delete powers;
    delete musica;
    delete sorteo;
    delete disparar;
    delete recto;
    delete gelato;
    delete hole;

}

void MainWindow::BossActive(bool t)
{
    if(t){ //activa el jefe
        bossOn=true;
        ui->bossHp->setVisible(true); //hace visible al jefe, inicializa la vida

        spawning->stop(); //desactiva la aparición de asteroides
        powers->stop(); //desactiva la aparición de poderes
        scene->addItem(jefe);
        sortear(); // desactiva uno de sus cañones
        jefe->setPos(260,20); //posiciona al jefe en la parte superior de la pantalla

        sorteo->start(5000); //activa el timer que desactiva un cañon
        disparar->start(1000); // activa el timer que controla los disparos de las naves
        for(int i=0;i<5;i++){ //inicializa todos los cañones

            canones.at(i)->setPos(250+(i*64),150); //ubica el cañón bajo el jefe
            canones.at(i)->activo=true; //activa el cañón
            canones.at(i)->Muerto(false);
            canones.at(i)->vida= jefe->vidaCanon(); //inicializa la vida del cañón en función de la vida inicial del jefe
            scene->addItem(canones.at(i));
        }
        setCanones();

    }
    else{ //desactiva el jefe y los cañones
        ui->bossHp->setVisible(false); // hace invisible el inicador de vida del jefe
        bossOn=false;
        spawning->start(1000-int(puntaje/10)); //reinicia la aparición de asteroides en funcion del puntaje
        powers->start(5000); // inicia el timer de aparición de poderes
        sorteo->stop(); // desactica el sorteo de cañones
        disparar->stop(); // desactiva el disparo de cañones
        scene->removeItem(jefe); // remueve al jefe de la escena
        jefe->setPos(1000,1000); // mueve de posicion fuera del alcance de las naves
        for(int i=0;i<5;i++){
            canones.at(i)->setPos(1000,1000); //  mueve de posicion fuera del alcance de las naves
            canones.at(i)->activo=false; // desactivo el cañon
            scene->removeItem(canones.at(i));
        }
    }
}

void MainWindow::spawn()
{
    // inicia el timer de aparición de los asteroides en función del puntaje
    if(puntaje>100&&puntaje<=500) spawning->start(1200);
    else if(puntaje>500&&puntaje<=1000 ) spawning->start(1000);
    else if(puntaje>1000)spawning->start(1000-int(puntaje/10));
    else if(puntaje>=10000)spawning->start(10);
    int px = 90+rand()%631; // asigna una posición horizontal aleatoria
    drop * cosa = new drop(true);
    cosa->setPos(px,0); // posiciona el asteroide en la posición horizontal obtenida y en la parte superior de la pantalla
    scene->addItem(cosa); // se agrega a la escena
    drops.push_back(cosa); // se agrega a la lista de drops
}

void MainWindow::crearPoder(){

    int px = 90+rand()%631; // asigna una posición horizontal aleatoria
    drop * cosa = new drop(false);
    cosa->setPos(px,0); // posiciona el asteroide en la posición horizontal obtenida y en la parte superior de la pantalla
    scene->addItem(cosa); // se agrega a la escena
    pows.push_back(cosa); // se agrega a la lista de pows

}

void MainWindow::esconderRecto()
{
    scene->removeItem(recto);
    recto->setRect(0,0,0,0); // modifica a 0 sus dimensiones


}

void MainWindow::esconderGelato()
{
    scene->removeItem(gelato);
    gelato->setRect(0,0,0,0); // modifica a 0 sus dimensiones

}

void MainWindow::esconderAgujero()
{
    scene->removeItem(hole);
    hole->setRect(0,0,0,0); // modifica a 0 sus dimensiones
    holeOn=false; // desactiva el poder
}

void MainWindow::on_pushButton_clicked(){
    pausa(); // llama la funcion pausa
}

void MainWindow::pausa()
{
    // detiene los timer de las funciónes principales del juego
    animacion->stop();
    spawning->stop();
    powers->stop();
    musica->stop();
    disparar->stop();
    sorteo->stop();
    control->encendido(false); // desactiva el control
    MenuPausa *men;
    men=new MenuPausa();

    men->setmain(this);
    men->show(); // abre el menu de pausa

}

void MainWindow::reanudar()
{   animacion->start(50);
    if(!bossOn){ // si el jefe esta desactivado reinicia la aparicion de asteroides y poderes

        spawning->start(1000-(puntaje/10));
        powers->start(5000);
    }
    else{ // si el jefe esta activado y reinicia el sorteo y disparo de los cañones

        disparar->start(1000);
        sorteo->start(5000);
    }

    control->encendido(true); // activa el control
    musica->play(); //reproduce la música
}

void MainWindow::guardarDatos()
{
    ofstream archivo(partida); //crea o abre un archivo de salida con el nombre de la partida
    if(singlePlayer) archivo<<"1;"; //como primer dato, ingresa el numero de jugadores
    else archivo<<"2;";
    if(bossOn)archivo<<"1;";//luego, si el jefe está activo o no
    else archivo<<"0;";
    archivo<<to_string(puntaje)<<endl; //introduce el puntaje actual de la partida

    archivo<<player1->Vida()<<";"<<player1->Power()<<";"<<player1->x()<<";"<<player1->y()<<endl; //ingresa los datos de vida, poder y posición del jugador 1
    if(!singlePlayer) archivo<<player2->Vida()<<";"<<player2->Power()<<";"<<player2->x()<<";"<<player2->y()<<endl; //ingresa los datos de vida, poder y posición del jugador 2
    if(bossOn){ //si el jefe está activo
        archivo<<jefe->Vida(); //ingresa la vida del jefe
        for(int i=0;i<5;i++){ archivo<<";"<<canones.at(i)->vida;} //ingresa la vida de todos los cañones
        archivo<<endl;

    }
    archivo.close();

}

void MainWindow::cargarDatos(){


    ifstream file(partida); //abre un archivo de lectura con el nombre de la partida
    char linea[50]="", dato[15]="", dato2[10]="";
    int contador=0, contador2=0;
    file.getline(linea,50); //lee una linea
    if(linea[0]=='1') singlePlayer=true; //primer dato: número de jugadores
    else singlePlayer=false;
    if(linea[2]=='0'){ //segundo dato, jefe activo(1) o inactivo(0)
        bossOn=false;
        ui->bossHp->setVisible(false);
        BossActive(false);
    }
    else bossOn=true;

    for(int i=4;linea[i]!='\0';i++){
        dato[i-4]=linea[i]; //puntaje
    }

    //añade uno o los dos jugadores a la escena
    ui->graphicsView->scene()->addItem(player1);

    if(!singlePlayer){
         ui->graphicsView->scene()->addItem(player2);
         control->setMultiplayer(true);//habilita el control para dos jugadores
    }

    else{
        ui->label_3->close();//cierra las etiquetas del jugador 2
        ui->hp2->close();
    }

    puntaje=atoi(dato); //convierte el puntaje de char[] a entero

    spawning->start(1000-(puntaje/10)); //inicia la aparición de asteroides en función del puntaje

    for(int i=0;dato[i]!='\0';i++) dato[i]='\0';
    file.getline(linea,50);//lee línea por línea el resto del archivo

    while(linea[contador]!=';'){
        dato[contador]=linea[contador];
        contador++;
    }

    player1->setVida(atoi(dato)); //vida del jugador 1
    for(int i=0;dato[i]!='\0';i++) dato[i]='\0';
    dato[0]=linea[contador+1];
    player1->setPoder(atoi(dato));//poder del jugador 1
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
    player1->setPos(atoi(dato),atoi(dato2)); //posición del jugador 1
    contador=0;
    contador2=0;
    for(int i=0;dato[i]!='\0';i++) dato[i]='\0'; for(int i=0;dato2[i]!='\0';i++) dato2[i]='\0';

    if(!singlePlayer){ //si hay otro jugador, lee sus datos
        file.getline(linea,50);

        while(linea[contador]!=';'){
            dato[contador]=linea[contador];
            contador++;
        }
        player2->setVida(atoi(dato)); //vida jugador 2
        for(int i=0;dato[i]!='\0';i++) dato[i]='\0';
        dato[0]=linea[contador+1];
        player2->setPoder(atoi(dato));// poder jugador 2
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
        player2->setPos(atoi(dato),atoi(dato2)); //posición del jugador 2
        contador=0;
        contador2=0;
        for(int i=0;dato[i]!='\0';i++) dato[i]='\0'; for(int i=0;dato2[i]!='\0';i++) dato2[i]='\0';
    }

    if(bossOn){ //si el jefe está activo, lee sus datos
        BossActive(true);
        //asigna el nombre del jefe en función del puntaje
        if(puntaje>=1000&&puntaje<1050) jefe->setVillano("augusGalactus");
        else if(puntaje>=3500&&puntaje<3550) jefe->setVillano("augusGalactus2");
        if(puntaje>=6500&&puntaje<6550) jefe->setVillano("augusGalactus3");

        setCanones();
        file.getline(linea,50);
        contador=0;
        contador2=0;
        //lee los datos de los cañones
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
            if(canones.at(i)->vida<=0) canones.at(i)->Muerto(true);//inicializa el cañon como muerto si la vida está bajo el mínimo
        }
    }
    file.close();


}

void MainWindow::animar(){
    if(musica->state()!=QMediaPlayer::PlayingState){ musica->play();  } //si la música no se está reproduciendo, la reinicia
    ui->hp->display(QString::number(player1->Vida())); //muestra la vida del jugador 1
    if(!singlePlayer) ui->hp2->display(QString::number(player2->Vida())); //si el jugador 2 está activo, muestra su vida
    ui->puntos->display(QString::number(puntaje)); // muestra el puntaje
    if(ui->bossHp->isVisible()){
        int vidaTotal= jefe->Vida();
        for(int i=0; i<5; i++ ){
            vidaTotal+=canones.at(i)->vida; //la vida total como la suma de la vida del jefe y las de sus cañones
        }
        ui->bossHp->setText(QString::fromStdString(to_string(vidaTotal))); //si el jefe está activo, muestra su nivel de vida
    }
    if(singlePlayer && player1->Vida()<=0){ //si el unico jugador está muerto, termina la partida
        //se detienen todos los timers
        animacion->stop();
        spawning->stop();
        powers->stop();
        musica->stop();
        disparar->stop();
        sorteo->stop();
        control->encendido(false); //se desactiva el control
        MenuPausa *men;
        men=new MenuPausa();
        men->esconder();
        men->setmain(this);
        men->show(); //abre el menú de pausa
        player1->setPixmap(QPixmap(":/images/damage.png")); //cambia la imagen de la nave a la de muerte
    }

    else if(!singlePlayer){  //si es multijugador
        if(player1->Vida()<=0){ //si el jugador 1 muere
            control->setvivo1(false);
            player1->setPixmap(QPixmap(":/images/damage.png"));//cambia la imagen de la nave a la de muerte
            ui->hp->setVisible(false); //desaparece de la escena su barra de salud

        }
        if(player2->Vida()<=0){
            control->setvivo2(false);
            player2->setPixmap(QPixmap(":/images/damage.png"));//cambia la imagen de la nave a la de muerte
            ui->hp2->setVisible(false); //desaparece de la escena su barra de salud
        }
        if(player1->Vida()<=0 && player2->Vida()<=0){ //si ambos jugadores están muertos, se termina la partida
            //se detienen todos los timers
            animacion->stop();
            spawning->stop();
            powers->stop();
            musica->stop();
            disparar->stop();
            sorteo->stop();
            control->encendido(false);//se desactiva el control
            MenuPausa *men;
            men=new MenuPausa();
            men->esconder();
            men->setmain(this);
            men->show(); //abre el menú de pausa
        }
    }

    if(!bossOn){ //si el jefe está inactivo, se analiza si se llegó al puntaje para activarlo
        //se inicializa la apariencia y nivel de vida del jefe según el puntaje alcanzado
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

    if(bossOn&&jefe->Vida()<=0){ //si el jefe está activo y su nivel de vida está debajo del mínimo
        BossActive(false); //desactiva el jefe
        puntaje+=100; //suma 100 puntos al puntaje total
        //crea y posiciona un poder tipo cura
        drop* cosa= new drop(false);
        cosa->setType("cura");
        cosa->setPos(jefe->x()+130,jefe->y());
        scene->addItem(cosa);
        pows.push_back(cosa);
    }

    //análisis de colisiones entre balas y entes amigos y enemigos. las balas y poderes que cumplen su función son enviados a sus respectivas listas "basura"

    for(int i=canones.size()-1;i>=0;i--){//para cada cañón..
        for(int h=balas.size()-1;h>=0;h--){
            if(canones.at(i)->collidesWithItem(balas.at(h))){//se analiza la colisión con cada bala
                if(canones.at(i)->vida<=0&&canones.at(i)->activo){ //si el cañón llega a un nivel de vida mínima
                    canones.at(i)->Muerto(true);
                    canones.at(i)->activo=false;
                    //"mata" al cañón (lo desactiva)
                }
                if(canones.at(i)->activo) canones.at(i)->vida-=balas.at(h)->Efecto();
                BasuraBalas.append(balas.at(h)); //añade la bala al basurero

            }
        }
    }


    for(int i=balasEnemigas.size()-1;i>=0;i--){//para cada bala enemiga
        balasEnemigas.at(i)->move(); // mueve las balas enemigas
        if(balasEnemigas.at(i)->collidesWithItem(player1)||balasEnemigas.at(i)->collidesWithItem(player2)){ // si la bala colisiono con una nave
            if(balasEnemigas.at(i)->collidesWithItem(player1)) // si la bala colisiono con el jugador 1
            player1->setVida(player1->Vida()-balasEnemigas.at(i)->Efecto()); // baja la vida de la nave
            if(balasEnemigas.at(i)->collidesWithItem(player2)) // si la bala colisiona con el jugador 2
                player2->setVida(player2->Vida()-balasEnemigas.at(i)->Efecto()); // baja la vida de la nave

            BasuraEnemigas.append(balasEnemigas.at(i)); // se agrega la bala a la lista de basura


        }
        else if(balasEnemigas.at(i)->y()>500){ // si la bala supera el limite superior
            BasuraEnemigas.append(balasEnemigas.at(i)); // se agrega la bala a la lista de basura

        }
        else{
            for(int h=balas.size()-1;h>=0;h--){
                if(balasEnemigas.at(i)->collidesWithItem(balas.at(h))){ // si la bala enemiga colisiona con una bale de una nave
                    BasuraEnemigas.append(balasEnemigas.at(i)); // se agrega la bala a la lista de basura


                    BasuraBalas.append(balas.at(h)); // se agrega la bala a la lista de basura

                    break;
                }
            }
        }

    }

    for(int w=balas.size()-1;w>=0;w--){
        balas.at(w)->move();//mueve la bala
        if(balas.at(w)->collidesWithItem(jefe)){ // si la bala colisiono con el jefe
            jefe->setVida(jefe->Vida()-balas.at(w)->Efecto());//baja la vida al jefe, en funcion del daño de la bala
            BasuraBalas.append(balas.at(w));//lleva la bala a la basura

        }
        else if (balas.at(w)->y()<=0) {
            BasuraBalas.append(balas.at(w));//si la bala se pasa de la parte superior de la pantalla, la elimina


        }
        else{
            for(int i=drops.size()-1;i>=0;i--){//para cada drop...
                if(balas.at(w)->collidesWithItem(drops.at(i))&&drops.at(i)->Efecto()>0){//si la bala choca con el drop...
                    drops.at(i)->setEfecto(drops.at(i)->Efecto()-balas.at(w)->Efecto());//baja el daño al asteroide
                    BasuraBalas.append(balas.at(w));//lleva la bala a la basura

                    puntaje+=10;//aumenta el puntaje
                    break;
                }
            }
        }
    }

    for(int i=drops.size()-1;i>=0;i--){//para cada drop
        if(drops.at(i)->Efecto()>0){ //si aún tiene efecto...
            if(drops.at(i)->collidesWithItem(recto)){//si choca con el escudo
                drops.at(i)->setVel(drops.at(i)->VelX(),(drops.at(i)->VelY())*(-0.8));//rebota con un coeficiente de restitución de 0.8
            }
            if(drops.at(i)->collidesWithItem(gelato)){//si está en contacto con la masa viscosa
                float Vcuad, angulo, vy=drops.at(i)->VelY(), vx=drops.at(i)->VelX(), ax, ay;
                int radio, masa;
                if(drops.at(i)->Type()=="asteroideB"){radio=2;masa=100;}
                else if(drops.at(i)->Type()=="asteroideS"){radio=1;masa=30;}
                angulo= atan2(vy,vx);
                Vcuad= (vy*vy)+(vx*vx);
                ax= -(10*Vcuad*(radio*radio)*cos(angulo))/masa;
                ay= -(10*Vcuad*(radio*radio)*sin(angulo))/masa;

                drops.at(i)->setVel(drops.at(i)->VelX()+(ax*0.1),drops.at(i)->VelY()+(ay*0.1)); //se mueve desacelerada por el medio
            }

            if(holeOn) drops.at(i)->move(1,hole->x(),hole->y());//si el agujero negro está activo, se mueve acelerado por la atracción gravitacional hacia las naves
            else{
                if(singlePlayer) drops.at(i)->move(1,player1->x(),player1->y());
                else drops.at(i)->move(1,player1->x(),player1->y(),player2->x(),player2->y());
            }

            if(drops.at(i)->collidesWithItem(player1)||drops.at(i)->collidesWithItem(player2)){// si el drop colisiona con alguno de los jugadores
                if(drops.at(i)->collidesWithItem(player1)&&player1->Vida()>0){
                    player1->setVida(player1->Vida()-drops.at(i)->Efecto());//se aplica el efecto sobre el jugador 1
                    BasuraDrops.append(drops.at(i));//se envia el drop a la basura
                }

                if(drops.at(i)->collidesWithItem(player2)&&player2->Vida()>0){
                    player2->setVida(player2->Vida()-drops.at(i)->Efecto());//se aplica el efecto sobre el jugador 1
                    BasuraDrops.append(drops.at(i)); //se envia el drop a la basura
                }



            }
            else if(drops.at(i)->y()>500){//si el drop supera la posicion mínima en pantalla
                BasuraDrops.append(drops.at(i));//se envia el drop a la basura

                player1->setVida(player1->Vida()-drops.at(i)->Efecto());//se aplica el efecto al jugador 1
                if(!singlePlayer) player2->setVida(player2->Vida()-drops.at(i)->Efecto());//si el jugaador 2 está activo, se aplica el efecto al jugador 2
            }
            else if(drops.at(i)->x()<50||drops.at(i)->x()>820){// si el drop supera la posicion mínima o máxima horizontal en pantalla...
                BasuraDrops.append(drops.at(i));//se envia el drop a la basura
            }
            else if(drops.at(i)->collidesWithItem(hole)){ //si el drop choca con el agujero negro...
                BasuraDrops.append(drops.at(i));//se envia el drop a la basura

            }

        }
        else{
            BasuraDrops.append(drops.at(i));//se envia el drop a la basura

        }

    }
    for(int i=pows.size()-1;i>=0;i--){
        pows.at(i)->move();//se mueve el poder
        if(pows.at(i)->collidesWithItem(player2)||pows.at(i)->collidesWithItem(player1)){//si el poder colisiona con alguno de los jugadores, se aplica el efecto según el tipo

            if(pows.at(i)->Type()=="cura"){
                if(pows.at(i)->collidesWithItem(player1)) player1->setVida(player1->Vida()+100);
                if(pows.at(i)->collidesWithItem(player2)) player2->setVida(player2->Vida()+100);
            }
            else if(pows.at(i)->Type()=="veneno"){
                if(pows.at(i)->collidesWithItem(player1)) player1->setVida(player1->Vida()/2);
                if(pows.at(i)->collidesWithItem(player2)) player2->setVida(player2->Vida()/2);
            }
            else if(pows.at(i)->Type()=="mejora"){
                if(pows.at(i)->collidesWithItem(player1)) player1->setPoder(player1->Power()+1);
                if(pows.at(i)->collidesWithItem(player2)) player2->setPoder(player2->Power()+1);
            }
            else if(pows.at(i)->Type()=="escudo"){//activa el escudo
                 recto->setRect(0,0,720,30);
                 recto->setBrush(Qt::green);
                 recto->setPos(50,300);
                 scene->addItem(recto);
                 QTimer::singleShot(10000,this,SLOT(esconderRecto()));
            }
            else if(pows.at(i)->Type()=="gelato"){//activa la masa viscosa
                gelato->setRect(0,0,720,150);
                gelato->setBrush(Qt::blue);
                gelato->setPos(50,150);
                scene->addItem(gelato);
                QTimer::singleShot(10000,this,SLOT(esconderGelato()));
            }
            else if(pows.at(i)->Type()=="agujero"){//activa el agujero negro
                hole->setRect(0,0,50,50);
                hole->setBrush(Qt::black);
                hole->setPos(380,225);
                scene->addItem(hole);
                holeOn=true;
                QTimer::singleShot(10000,this,SLOT(esconderAgujero()));

            }




            BasuraPows.append(pows.at(i));//agrega el poder a la basura


        }
        else if(pows.at(i)->y()>500){
            BasuraPows.append(pows.at(i));//agrega el poder a la basura


        }

    }
    //comienza a borrar cada una de las basuras
    for(int i=BasuraBalas.size()-1;i>=0;i--){
        for(int j=balas.size()-1;j>=0;j--){
            if(BasuraBalas.at(i)==balas.at(j)){
                scene->removeItem(BasuraBalas.at(i));
                BasuraBalas.at(i)->~proyectil();
                BasuraBalas.removeAt(i);
                balas.removeAt(j);
                break;
            }
        }
    }

    for(int i=BasuraDrops.size()-1;i>=0;i--){
        for(int j=drops.size()-1;j>=0;j--){
            if(BasuraDrops.at(i)==drops.at(j)){
                scene->removeItem(BasuraDrops.at(i));
                BasuraDrops.at(i)->~drop();
                BasuraDrops.removeAt(i);
                drops.removeAt(j);
                break;
            }
        }
    }

    for(int i=BasuraEnemigas.size()-1;i>=0;i--){
        for(int j=balasEnemigas.size()-1;j>=0;j--){
            if(BasuraEnemigas.at(i)==balasEnemigas.at(j)){
                scene->removeItem(BasuraEnemigas.at(i));
                BasuraEnemigas.at(i)->~proyectil();
                BasuraEnemigas.removeAt(i);
                balasEnemigas.removeAt(j);
                break;
            }
        }
    }

    for(int i=BasuraPows.size()-1;i>=0;i--){
        for(int j=pows.size()-1;j>=0;j--){
            if(BasuraPows.at(i)==pows.at(j)){
                scene->removeItem(BasuraPows.at(i));
                BasuraPows.at(i)->~drop();
                BasuraPows.removeAt(i);
                pows.removeAt(j);
                break;
            }
        }
    }

}


void MainWindow::shoot()
{
    for(int i=canones.size()-1;i>=0;i--){//para cada cañón del jefe que esté activo, dispara
        if(canones.at(i)->activo){
            proyectil* p= new proyectil;
            p->setMalo(20);// corrompe la bala(movimiento contrario y efecto negativo sobre las naves)
            p->setPos(canones.at(i)->x()+26,canones.at(i)->y()+31);
            balasEnemigas.push_back(p);//añade la bala enemiga a la lista de balas enemigas
            scene->addItem(p);
            //hace lo anterior otras dos veces
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


void MainWindow::sortear(){//sortea cual cañón del jefe que aun no está destruido será desactivado, y activa el que se encontraba en este estado
    int w= CanonPausado, vmax=0;
    bool muertos=true;
    if(canones.at(CanonPausado)->vida>0)canones.at(CanonPausado)->activo=true;//si el cañón pausado sigue sin ser destruido, lo activa
    for(int i=canones.size()-1;i>=0;i--){//busca el cañón con más vida, distinto al cañón que estaba pausado antes
        if(canones.at(i)->vida>0)muertos=false; //busca si hay cañones muertos
        else{

            canones.at(i)->Muerto(true);

        }
        if(canones.at(i)->vida>vmax&&i!=w) {
            CanonPausado=i;
            vmax=canones.at(i)->vida;
        }
    }
    if(CanonPausado!=w)
    canones.at(CanonPausado)->activo=false;//desactiva el cañón seleccionado
    if(muertos){//si todos están muertos
        disparar->stop();//paran los disparos
        sorteo->stop();//se detiene el sorteo

        for(int i=canones.size()-1;i>=0;i--){//remueve los cañones de la escena
            canones.at(i)->Muerto(true);
            canones.at(i)->setPos(1000,1000);
            scene->removeItem(canones.at(i));
        }
    }
}

void MainWindow::setCanones()
{
    if(jefe->Vida()>0){//si el jefe sigue vivo, crea los cañones y los configura dependiendo su nivel de dificultad
        if(jefe->nombre=="augusGalactus"){
            for(int i=0;i<5;i++){

                canones.at(i)->setPos(250+(i*64),150);//posición
                canones.at(i)->activo=true;//lo activa
                canones.at(i)->Muerto(false);//vivo
                canones.at(i)->vida=2000;//inicializar vida
                scene->addItem(canones.at(i));
            }
        }
        else if(jefe->nombre=="augusGalactus2"){
            for(int i=0;i<5;i++){

                canones.at(i)->setPos(250+(i*64),150);//posición
                canones.at(i)->activo=true;//lo activa
                canones.at(i)->Muerto(false);//vivo
                canones.at(i)->vida=5000;//inicializar vida
                scene->addItem(canones.at(i));
                canones.at(i)->setPixmap(QPixmap(":/images/bossPeque2.png"));
            }
        }
        else if(jefe->nombre=="augusGalactus3"){
            for(int i=0;i<5;i++){

                canones.at(i)->setPos(250+(i*64),150);//posicion
                canones.at(i)->activo=true;//lo activa
                canones.at(i)->Muerto(false);//vivo
                canones.at(i)->vida=7000;//inicializar vida
                scene->addItem(canones.at(i));
                canones.at(i)->setPixmap(QPixmap(":/images/bossPeque3.png"));
            }
        }
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    control->conectar();//activa lectura de arduino
}
