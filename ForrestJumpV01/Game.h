#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include "Player.h"
#include "Obstacle.h"
#include "HUD.h"


class Game : public QGraphicsView{
public:
    Game(QWidget* parent = nullptr);



private:
    const int xSize = 800;     // game scene width
    const int ySize = 600;     // game scene height
    void setUpObstacleTimer();
    QTimer* obstacleTimer;

    QGraphicsScene* scene;
    Player* player;
    HUD* hud;
};

#endif // GAME_H
