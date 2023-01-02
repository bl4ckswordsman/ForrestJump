#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QAudioOutput>



Player::Player(QGraphicsItem *parent): QGraphicsRectItem(parent){
    // setting up the jumping sound effect
    jumpSFX = new QMediaPlayer();
    QAudioOutput* audioOutput2 = new QAudioOutput();
    jumpSFX->setAudioOutput(audioOutput2);
    audioOutput2->setVolume(0.5);
    jumpSFX->setSource(QUrl("qrc:/audio/resources/jump_dbz.mp3"));

    this->setRect(0,0,xSz,ySz); // changing the rect from 0x0 (default) to 100x100 pixels
    // making the player focusable and setting focus on it
    this->setPos(5,500);
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    jumpAnimation = new QPropertyAnimation(this, "y", this);
    jumpAnimation->setDuration(300);
    jumpAnimation->setEasingCurve(QEasingCurve::InQuad);



}


void Player::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Space){
        //setPos(x(), y()-10);
        jump();

        // playing jumping sound effect
        if (jumpSFX->playbackState()  == QMediaPlayer::PlayingState) {
            jumpSFX->setPosition(0);
        }
        else if (jumpSFX->playbackState() == QMediaPlayer::StoppedState) {
            jumpSFX->play();
        }



        /*QPropertyAnimation* animation = new QPropertyAnimation(this, "y", this);
        animation->setDuration(500);
        animation->setStartValue(scenePos().y());
        animation->setEasingCurve(QEasingCurve::InQuad);
        animation->setEndValue(200);
        animation->start();
        //QPropertyAnimation* animation2 = new QPropertyAnimation(this, "y", this);
        //animation2->setDuration(500);
        //animation2->setStartValue(scenePos().y());
        //animation2->setEasingCurve(QEasingCurve::InQuad);
        connect(animation, &QPropertyAnimation::finished,this);
        //animation->setEndValue(500);

        animation->start();*/

    }
}

void Player::jump(){
    if (isJumping){
        return;
    }
    isJumping = true;
    jumpAnimation->setStartValue(y());   //pos());
    jumpAnimation->setEndValue(y()-200);     //QPointF(pos().x(), pos().y() - 200));
    // Connecting the animation's finished signal to the jumpFinished slot
    connect(jumpAnimation, &QPropertyAnimation::finished, this, &Player::fallDown);
    qDebug() << "jumping";
    jumpAnimation->start();
}

int Player::getXSz() const{
    return xSz;
}

int Player::getYSz() const{
    return ySz;
}

void Player::setY(qreal y){
    //    setPos(QPointF(pos().x(), y-pos().y() ));
    qDebug() << this->pos();
    //moveBy(0,y - this->pos().y());
    //qDebug() << this->y();
    //m_y = y;
    setPos(QPointF(pos().x(), y));

}

qreal Player::y() const{
    //return m_y;
    return pos().y();
}

void Player::fallDown(){
    // Disconnecting the finished signal to prevent the slot from being called multiple times
    jumpAnimation->disconnect(this);
    jumpAnimation->setStartValue(y());   //pos());
    jumpAnimation->setEndValue(y()+200);     //QPointF(pos().x(), pos().y() + 200));
    connect(jumpAnimation, &QPropertyAnimation::finished, this, &Player::jumpFinished);
    qDebug() << "falling down";
    jumpAnimation->start();
}

void Player::jumpFinished(){
    isJumping = false;
    jumpAnimation->disconnect(this);
}



