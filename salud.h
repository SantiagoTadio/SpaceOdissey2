#ifndef SALUD_H
#define SALUD_H

#include <QGraphicsTextItem>


class salud: public QGraphicsTextItem
{
public:
    salud(QGraphicsTextItem * parent=0);
    void modificar(int val){valor+=val; actualizarValor();}
    int getValor(){return valor;}

private:
    int valor;
    void actualizarValor(){setPlainText(QString("SALUD: ")+QString::number(valor));}
};

#endif // SALUD_H
