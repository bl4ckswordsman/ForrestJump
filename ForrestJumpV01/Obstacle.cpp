#include "Obstacle.h"
#include <QRandomGenerator>
#include <QDebug>

Obstacle::Obstacle(QGraphicsItem* parent):
    QGraphicsPixmapItem(parent){
    //setRect(0,0,100,100);
    setPixmap(QPixmap(":/images/resources/obstacle_tree.png"));
    int xRandomizer = QRandomGenerator::global()->bounded(200);
    setPos(QPoint(0,0)+QPoint(660 + xRandomizer,500));
    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setEndValue(-660);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1500);
    connect(xAnimation, &QPropertyAnimation::finished,[=](){
        qDebug() << "Animation finished";
        scene()->removeItem(this);
        delete this;
    });

    xAnimation->start();


}

Obstacle::~Obstacle(){
    qDebug() << "Obstacle deleted";

}

void Obstacle::setX(qreal x){
    moveBy(x-this->x(),0);
    //qDebug() << this->x();
}
