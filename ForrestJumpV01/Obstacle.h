#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QPropertyAnimation>
#include <QGraphicsScene>

class Obstacle : public QObject, public QGraphicsRectItem{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)// NOTIFY nameChanged)
public:
    explicit Obstacle(QGraphicsRectItem* parent = nullptr);
    ~Obstacle();
    void setX(qreal x);

private:
    QPropertyAnimation* xAnimation;

};

#endif // OBSTACLE_H
