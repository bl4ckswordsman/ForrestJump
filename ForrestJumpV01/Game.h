#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include "Player.h"
#include "Obstacle.h"

class Game : public QGraphicsView{
public:
    Game(QWidget* parent = nullptr);

    QGraphicsScene* scene;
    Player* player;
private:
    const int xSize = 800;     // game scene width
    const int ySize = 600;     // game scene height
    void setUpObstacleTimer();
    QTimer* obstacleTimer;
};

#endif // GAME_H
