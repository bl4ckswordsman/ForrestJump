#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QGraphicsScene>


class Obstacle : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)// NOTIFY nameChanged)
public:
    explicit Obstacle(QGraphicsItem* parent = nullptr);
    ~Obstacle();
    void freezeInPlace();
public slots:
    void setX(qreal x);


private:
    QPropertyAnimation* xAnimation;


};

#endif // OBSTACLE_H
