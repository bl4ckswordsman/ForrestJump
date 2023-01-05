#include "Game.h"
#include "Obstacle.h"
#include <QPropertyAnimation>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QFont>


Game::Game(QWidget *parent): QGraphicsView(parent){
    initiateGameElements();

}

void Game::collisionCheck(){

}

void Game::initiateGameElements(){

    // creating the game scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,xSize,ySize);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(xSize,ySize);

    // creating the player
    player = new Player();
    scene->addItem(player);
    collisionT = new QTimer();
    connect(collisionT,SIGNAL(timeout()),this,SLOT(gameOver()));
    collisionT->start(50);

    setUpObstacleTimers();
    // connecting a timer to Obstacle::updateCollisionCont(), to check player-obstacle collisions
    /*auto collisionT = new QTimer();
    connect(collisionT, SIGNAL(timeout()), obs, SLOT(updateCollisionCont()));
    collisionT->start(50);*/

    // creating the heads up display
    hud = new HUD();
    hud->setPos(5,5);
    scene->addItem(hud);

    // playing background music
    music = new QMediaPlayer();
    QAudioOutput* audioOutput = new QAudioOutput();
    music->setAudioOutput(audioOutput);
    music->setSource(QUrl("qrc:/audio/resources/theme_OP.mp3"));
    music->play();
}

void Game::setUpObstacleTimers(){
    obstacleTimer = new QTimer(this);
    connect(obstacleTimer,&QTimer::timeout,[=](){
        Obstacle* obstacle = new Obstacle();
        //obstacle->setPos(700,500);
        scene->addItem(obstacle);

        /*for (int i=0, n = obstacle->collidingItemsContainer.size(); i<n; i++){
            if (typeid(*(obstacle->collidingItemsContainer[i])) == typeid(Player)){
                gameOver();
            }
        }*/

    });
    obstacleTimer->start(1000);


}

void Game::freezeGame(){
    obstacleTimer->stop();
    collisionT->stop();
    player->freezeInPlace();
    QList<QGraphicsItem*> sceneItems = items();
    for (auto item:sceneItems){
        Obstacle* obst = dynamic_cast<Obstacle*>(item);
        if (obst){
            obst->freezeInPlace();
        }
    }
    hud->stopTimer();

}

void Game::gameOver(){

    player->updateCollisionCont();
    if (!player->collidingItemsContainer.isEmpty()){
        freezeGame();
        music->stop();
        music = new QMediaPlayer();
        QAudioOutput* audioOutput2 = new QAudioOutput();
        music->setAudioOutput(audioOutput2);
        music->setSource(QUrl("qrc:/audio/resources/gameover.mp3"));
        music->play();
        auto currentScore = hud->getScore();
        //scene->clear();
        this->disconnect();
        /*auto scene2 = new QGraphicsScene();
        scene2->setSceneRect(0,0,xSize,ySize);
        setScene(scene2);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setFixedSize(xSize,ySize);
        //this->initiateGameElements();*/

        auto gameOVER = new QGraphicsTextItem;
        gameOVER->setDefaultTextColor(Qt::red);
        gameOVER->setFont(QFont("times",30));
        gameOVER->setPlainText(QString("GAME OVER! Your score: ")+QString::number(currentScore));
        gameOVER->setPos(150,100);
        scene->addItem(gameOVER);

        auto playAgainB = new QPushButton(nullptr);
        playAgainB->setText("New Game");
        playAgainB->move(350, 200);
        playAgainB->setFixedSize(100, 50);
        QFont font("Arial", 12);
        playAgainB->setFont(font);
        scene->addWidget(playAgainB);
        connect(playAgainB, &QPushButton::clicked, this, &Game::newGame);

    }

    //disconnect
}

void Game::newGame(){
    /*scene->clear();
    delete this->player;
    this->player = new Player();

    this->hud = new HUD();*/
    delete this->hud;
    initiateGameElements();
}
