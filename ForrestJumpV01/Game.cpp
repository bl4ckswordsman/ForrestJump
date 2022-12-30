#include "Game.h"
#include <QPropertyAnimation>

Game::Game(QWidget *parent): QGraphicsView(parent){
    // creating the game scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,xSize,ySize);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(xSize,ySize);

    // creating the player
    player = new Player();
    //player->setRect(0,0,100,100); // change the rect from 0x0 (default) to 100x100 pixels
    //  player->setPos(5,ySize - player->getYSz()); //
    // add the player to the scene
    scene->addItem(player);

    setUpObstacleTimer();
//    Obstacle* obstacle = new Obstacle();
//    obstacle->setPos(700,500);
//    scene->addItem(obstacle);

}

void Game::setUpObstacleTimer(){
    obstacleTimer = new QTimer(this);
    connect(obstacleTimer,&QTimer::timeout,[=](){
        Obstacle* obstacle = new Obstacle();
        //obstacle->setPos(700,500);
        scene->addItem(obstacle);
    });
    obstacleTimer->start(1000);


}
