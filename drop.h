#ifndef DROP_H
#define DROP_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>



class drop: public QObject,
            public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    drop();
    ~drop();
public slots:
    void move();
private:
    int cont;
    int vel;
    QTimer * timer;

};

#endif // DROP_H
