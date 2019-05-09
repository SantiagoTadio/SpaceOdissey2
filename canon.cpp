#include "canon.h"

canon::canon()
{
    setPixmap(QPixmap(":/images/bossPeque.png"));  //imagen de nave regular
    vida=5000;
    activo=true;
}

void canon::Muerto(bool a)
{
    if(a){
        vida=0;
        activo=false;
        setPixmap(QPixmap(":/images/pequeDead.png"));// imagen de nave destruida
    }
    else{
        setPixmap(QPixmap(":/images/bossPeque.png")); //imagen de nave regular
        vida=5000;
        activo=true;
    }
}

