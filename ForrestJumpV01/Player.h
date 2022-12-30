#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QProperty>
#include <QPropertyAnimation>


class Player : public QObject, public QGraphicsRectItem{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    Player(QGraphicsItem *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    void jump();


    int getXSz() const;

    int getYSz() const;
    void setY(qreal Y);

    qreal y() const;

//public slots:
    //void spawnEnemies();
private:
    const int xSz = 100;
    const int ySz = 100;
    QPropertyAnimation* jumpAnimation;
    qreal m_y;
    bool isJumping = false;   //prevent double jumping
private slots:
    void fallDown();
    void jumpFinished();

};

#endif // PLAYER_H
