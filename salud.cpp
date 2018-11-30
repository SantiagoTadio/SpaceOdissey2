#include "salud.h"
#include <QGraphicsTextItem>
#include <QFont>

salud::salud(QGraphicsTextItem * parent): QGraphicsTextItem(parent)
{
    valor=0;
    actualizarValor();
    setDefaultTextColor(Qt::lightGray);
    setFont(QFont("BankGothic",32));

}
