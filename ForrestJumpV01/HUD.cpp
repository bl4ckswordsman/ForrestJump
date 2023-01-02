#include "HUD.h"
#include <QTimer>
#include <QFont>
#include <QDebug>

HUD::HUD(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // intializing score to 0
    score = 0;
    //setPlainText(QString("Score: ")+QString::number(score));

    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",16));

//    QTimer timer;

//    connect(&timer, SIGNAL(timeout()), this, SLOT(scoreIncrement()));
//    timer.start(1000); // 1000 ms = 1 second

    QTimer* timer = new QTimer(this);
    connect(timer,&QTimer::timeout,[=](){
        scoreIncrement();
    });
    timer->start(1000);

}

void HUD::scoreIncrement(){
    setPlainText(QString("Score: ")+QString::number(score++));
    qDebug() << score;
}
