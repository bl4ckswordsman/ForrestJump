/* DT079G Project - Forrest Jump game
 *  Amarildo Rajta 2023-01-07 */
#include "HUD.h"

#include <QFont>
#include <QDebug>

HUD::HUD(QGraphicsItem *parent): QGraphicsTextItem(parent), score(0){
    setDefaultTextColor(Qt::white);
    setFont(QFont("times",16));

    HUDTimer = new QTimer(this);
    //connecting the scoreIncrement() to a timer with 1Hz (1/second) frequency
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
