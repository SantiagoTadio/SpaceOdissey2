#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jugador.h"
#include <QGraphicsScene>
#include <QMediaPlayer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   scene = new QGraphicsScene;
   QMediaPlayer * musica = new QMediaPlayer;
   musica->setMedia(QUrl("qrc:/music/audio.mp3"));
   scene->setSceneRect(0,0,821,501);
   scene->setBackgroundBrush(QBrush(QImage(":/images/BG.png")));
   ui->graphicsView->setScene(scene);
   ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

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

void MainWindow::on_pushButton_clicked(){
    scene->setBackgroundBrush(QBrush(QImage(":/images/bg2.png")));
    ui->label_odissey->close();
    ui->comboBox->close();
    ui->comboBox_2->close();
    ui->label_2->close();
    ui->label_4->close();
    ui->label_info->close();
    ui->label_space->close();
    ui->plainTextEdit->close();
    ui->plainTextEdit_2->close();



    jugador * player = new jugador;
    player->setPos(385,411);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    ui->graphicsView->scene()->addItem(player);


    ui->pushButton->close();
}
