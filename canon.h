#ifndef CANON_H
#define CANON_H
#include <QGraphicsPixmapItem>

class canon: public QGraphicsPixmapItem
{
public:
    canon();
    int vida;
    bool activo; // booleano que determina si una nave enemiga está disparando (activo = true)
    void Muerto(bool a); // funcion que "mata" las naves enemigas cuando su vida llega a un nivel mínimo
    

};

#endif // CANON_H
