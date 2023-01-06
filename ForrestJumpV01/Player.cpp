#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QAudioOutput>
#include <QTimer>


Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    // setting up graphic
    setPixmap(QPixmap(":/images/resources/player_luffy.png"));
    this->setPos(5,500);
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    // setting up the jumping sound effect
    jumpSFX = new QMediaPlayer();
    QAudioOutput* audioOutput2 = new QAudioOutput();
    jumpSFX->setAudioOutput(audioOutput2);
    audioOutput2->setVolume(0.5);
    jumpSFX->setSource(QUrl("qrc:/audio/resources/jump_dbz.mp3"));

    // setting up the jump animation
    jumpAnimation = new QPropertyAnimation(this, "y", this);
    jumpAnimation->setDuration(300);
    jumpAnimation->setEasingCurve(QEasingCurve::InQuad);





}


void Player::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Space){
        if (jumpsAllowed){
            jump();

            // playing jumping sound effect, configuring playback scenarios
            if (jumpSFX->playbackState()  == QMediaPlayer::PlayingState) {
                jumpSFX->setPosition(0);
            }
            else if (jumpSFX->playbackState() == QMediaPlayer::StoppedState) {
                jumpSFX->play();
            }
        }
    }
}

void Player::jump(){

    if (isJumping){
        return;
    }
    isJumping = true;
    jumpAnimation->setStartValue(y());
    jumpAnimation->setEndValue(y()-200);
    // Connecting the animation's finished signal to the fallDown slot
    connect(jumpAnimation, &QPropertyAnimation::finished, this, &Player::fallDown);
    qDebug() << "jumping";
    jumpAnimation->start();

}

void Player::freezeInPlace(){
    jumpAnimation->stop();
    jumpsAllowed = false;
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

void Player::updateCollisionCont(){
    //storing collision information if player collides with obstacle
    collidingItemsContainer = collidingItems();
    /*if (!collidingItemsContainer.isEmpty())
        this->scene()->clear();*/
}



