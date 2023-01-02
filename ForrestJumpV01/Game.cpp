#include "Game.h"
#include <QPropertyAnimation>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>

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

    hud = new HUD();
    hud->setPos(5,5);
//    QTimer timer;
//    connect(&timer, SIGNAL(timeout()), hud, SLOT(scoreIncrement()));
//    timer.start(1000); // 1000 ms = 1 second
    scene->addItem(hud);



    // playing background music
    QMediaPlayer* music = new QMediaPlayer();
    QAudioOutput* audioOutput = new QAudioOutput();
    music->setAudioOutput(audioOutput);
    music->setSource(QUrl("qrc:/audio/resources/theme_OP.mp3"));
    music->play();

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
