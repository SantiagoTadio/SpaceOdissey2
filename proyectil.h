#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QGraphicsRectItem>

#include <QObject>
#include <QTimer>

class proyectil: public QObject,
                 public QGraphicsRectItem
{
    Q_OBJECT
public:
    proyectil();
    ~proyectil();

public slots:
    void move();
private:
    QTimer * timer;
};


#endif // PROYECTIL_H
