#include "HUD.h"

#include <QFont>
#include <QDebug>

HUD::HUD(QGraphicsItem *parent): QGraphicsTextItem(parent), score(0){

    //setPlainText(QString("Score: ")+QString::number(score));

    setDefaultTextColor(Qt::white);
    setFont(QFont("times",16));

//    QTimer timer;

//    connect(&timer, SIGNAL(timeout()), this, SLOT(scoreIncrement()));
//    timer.start(1000); // 1000 ms = 1 second

    HUDTimer = new QTimer(this);
    connect(HUDTimer,&QTimer::timeout,[=](){
        scoreIncrement();
    });
    HUDTimer->start(1000);

}

void HUD::scoreIncrement(){
        setPlainText(QString("Score: ")+QString::number(score));
        score++;
}

int HUD::getScore() const{
    if (score==0){
        return score;
    }
    return score-1;
}

void HUD::stopTimer(){
    HUDTimer->stop();
}
