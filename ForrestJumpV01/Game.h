#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <QMediaPlayer>
#include "Player.h"
#include "HUD.h"

//
//
//USE MORE auto
//

class Game : public QGraphicsView{
Q_OBJECT
public:
    Game(QWidget* parent = nullptr);
    //~Game();
public slots:
    void collisionCheck();
    void gameOver();
    void newGame();

private:
    void initiateGameElements();
    void setUpObstacleTimers();
    void freezeGame();
    void saveScore(int score);
    void checkHighScore(int score);
    const int xSize = 800;     // game scene width
    const int ySize = 600;     // game scene height


    QTimer* obstacleTimer;
    QTimer* collisionT;

    QGraphicsScene* scene;
    QGraphicsPixmapItem* bg;
    Player* player;
    HUD* hud;
    QMediaPlayer* music;
};

#endif // GAME_H
