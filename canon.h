#ifndef CANON_H
#define CANON_H
#include <QGraphicsPixmapItem>

class canon: public QGraphicsPixmapItem
{
public:
    canon();
    int vida;
    bool activo;
    void Muerto(bool a);
    

};

#endif // CANON_H
