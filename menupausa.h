#ifndef MENUPAUSA_H
#define MENUPAUSA_H

#include <QDialog>
#include "mainwindow.h"
#include "registro.h"
#include "inicio.h"
#include <QGraphicsScene>

namespace Ui {
class MenuPausa;
}

class MenuPausa : public QDialog
{
    Q_OBJECT

public:
    explicit MenuPausa(QWidget *parent = nullptr);
    ~MenuPausa();
    void setmain(MainWindow *m){mai=m;}
    void esconder();


private slots:
    void on_guardar_clicked();

    void on_partidas_clicked();

    void on_inicio_clicked();

    void on_salir_clicked();

    void on_reanudar_clicked();

private:
    Ui::MenuPausa *ui;
    QGraphicsScene* escena= new QGraphicsScene;
    MainWindow *mai;

};

#endif // MENUPAUSA_H
