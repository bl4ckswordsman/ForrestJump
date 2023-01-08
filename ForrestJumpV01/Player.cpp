/* DT079G Project - Forrest Jump game
 *  Amarildo Rajta 2023-01-07 */
#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>


Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    isJumping = false;
    // setting up graphic
    setPixmap(QPixmap(":/images/resources/player_luffy.png"));
    this->setPos(5,500);
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    // setting up the jumping sound effect
    jumpSFX = new QMediaPlayer();
    audioOutputJ = new QAudioOutput();
    jumpSFX->setAudioOutput(audioOutputJ);
    audioOutputJ->setVolume(0.5);
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
    // Preventing double jumping and delaying of the fall
    if (isJumping){
        return;
    }
    isJumping = true;
    jumpAnimation->setStartValue(y());
    jumpAnimation->setEndValue(y()-200);
    // Connecting the animation's finished signal to the fallDown slot
    connect(jumpAnimation, &QPropertyAnimation::finished, this, &Player::fallDown);
    jumpAnimation->start();
}

void Player::freezeInPlace(){
    jumpAnimation->stop();
    jumpsAllowed = false;
}

void Player::unfreeze(){
    jumpAnimation->start();
    jumpsAllowed = true;
}

void Player::setY(qreal y){
    setPos(QPointF(pos().x(), y));
}

qreal Player::y() const{
    return pos().y();
}

void Player::fallDown(){
    // Disconnecting the finished signal to prevent the slot from being called multiple times
    jumpAnimation->disconnect(this);
    jumpAnimation->setStartValue(y());
    jumpAnimation->setEndValue(y()+200);
    connect(jumpAnimation, &QPropertyAnimation::finished, this, &Player::jumpFinished);
    jumpAnimation->start();
}

void Player::jumpFinished(){
    isJumping = false;
    jumpAnimation->disconnect(this);
}

void Player::updateCollisionCont(){
    //storing player collision information
    collidingItemsContainer = collidingItems();
}



