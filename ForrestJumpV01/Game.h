#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <QMediaPlayer>
#include <QPushButton>
#include <QGraphicsProxyWidget>
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
public slots:
    void gameOver();
    void newGame();

private:
    void initiateGameElements();
    void setUpObstacleTimer();
    void playMusic();
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
    QAudioOutput* audioOutput;
    QMediaPlayer* music;
    QGraphicsTextItem* gameOverLabel;
    QGraphicsTextItem* highScoreLabel;
    QPushButton* playAgainB;
    QGraphicsProxyWidget* playAgainWidget;
};

#endif // GAME_H
