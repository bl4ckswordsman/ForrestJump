/* DT079G Project - Forrest Jump game
 *  Amarildo Rajta 2023-01-07 */
#include "Obstacle.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QTimer>


Obstacle::Obstacle(QGraphicsItem* parent):
    QGraphicsPixmapItem(parent){
    // setting up the pixmap
    setPixmap(QPixmap(":/images/resources/obstacle_tree.png"));
    int xRandomizer = QRandomGenerator::global()->bounded(200);
    setPos(QPoint(0,0)+QPoint(660 + xRandomizer,500));
    // setting up the animation
    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setEndValue(-150);      // animation ends at x=-150 (out of bounds)
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1500);
    connect(xAnimation, &QPropertyAnimation::finished,[=](){
        //qDebug() << "Animation finished";
        scene()->removeItem(this);      //removes and deletes obstacle when animation ends
        delete this;
    });

    xAnimation->start();
}

/*Obstacle::~Obstacle(){
    qDebug() << "Obstacle deleted";

}*/

void Obstacle::freezeInPlace(){
    xAnimation->stop();
}

void Obstacle::startAnimation(){
    xAnimation->start();
}

void Obstacle::setX(qreal x){
    moveBy(x - this->x(),0);
    //qDebug() << this->x();
}


