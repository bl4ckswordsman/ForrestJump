#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QProperty>
#include <QPropertyAnimation>
#include <QMediaPlayer>
#include <QAudioOutput>


class Player : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    Player(QGraphicsItem *parent = nullptr);

    void keyPressEvent(QKeyEvent *event);
    void jump();
    void freezeInPlace();
    void unfreeze();

    void setY(qreal Y);

    qreal y() const;

    QList<QGraphicsItem*> collidingItemsContainer;
    bool jumpsAllowed{false};
public slots:
    void updateCollisionCont();
private:
    const int xSz = 100;
    const int ySz = 100;

    QPropertyAnimation* jumpAnimation;

    bool isJumping;   //prevent double jumping
    QMediaPlayer* jumpSFX;    //jumping sound effect
    QAudioOutput* audioOutputJ;
private slots:
    void fallDown();
    void jumpFinished();

};

#endif // PLAYER_H
