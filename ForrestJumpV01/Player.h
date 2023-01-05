#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QProperty>
#include <QPropertyAnimation>
#include <QMediaPlayer>



class Player : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    Player(QGraphicsItem *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    void jump();
    void freezeInPlace();

    int getXSz() const;

    int getYSz() const;
    void setY(qreal Y);

    qreal y() const;

    QList<QGraphicsItem*> collidingItemsContainer;

public slots:
    //void spawnEnemies();
    void updateCollisionCont();
private:
    const int xSz = 100;
    const int ySz = 100;
    QPropertyAnimation* jumpAnimation;
    qreal m_y;
    bool isJumping = false;   //prevent double jumping
    QMediaPlayer* jumpSFX;    //jumping sound effect
private slots:
    void fallDown();
    void jumpFinished();

};

#endif // PLAYER_H
