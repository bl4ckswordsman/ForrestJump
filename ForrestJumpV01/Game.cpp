/*! \author Amarildo Rajta \date 2023-01-07
 *  \details DT079G Project - Forrest Jump game */
//! \file
//! \code Game.cpp

#include "Game.h"
#include "Obstacle.h"
#include <QPropertyAnimation>
#include <QAudioOutput>
#include <QGraphicsTextItem>
#include <QFont>
#include <QGraphicsPixmapItem>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <algorithm>


Game::Game(QWidget *parent): QGraphicsView(parent){
    initiateGameElements();
}

// Function object to freeze all obstacles
struct FreezeObstacles{
    void operator()(QGraphicsItem* item)
    {
        Obstacle* obst = dynamic_cast<Obstacle*>(item);
        if (obst) {
            obst->freezeInPlace();
        }
    }
};


void Game::initiateGameElements(){
    // creating the game scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,xSize,ySize);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(xSize,ySize);

    // adding background image
    bg = new QGraphicsPixmapItem();
    bg->setPixmap(QPixmap(":/images/resources/bg.png"));
    bg->setPos(0,0);
    scene->addItem(bg);

    // creating the player
    player = new Player();
    player->jumpsAllowed = true;
    scene->addItem(player);
    collisionT = new QTimer();
    connect(collisionT,SIGNAL(timeout()),this,SLOT(gameOver()));
    collisionT->start(50);

    setUpObstacleTimer();

    // creating the heads up display
    hud = new HUD();
    hud->setPos(5,5);
    scene->addItem(hud);

    // playing background music
    playMusic();

    // initializing components that will be used later
    gameOverLabel = nullptr;
    highScoreLabel = nullptr;
    playAgainWidget = nullptr;
    playAgainB = nullptr;
}


void Game::setUpObstacleTimer(){
    obstacleTimer = new QTimer(this);
    connect(obstacleTimer,&QTimer::timeout,[=](){
        Obstacle* obstacle = new Obstacle();
        scene->addItem(obstacle);
    });
    obstacleTimer->start(1000);


}


void Game::playMusic(){
    music = new QMediaPlayer();
    audioOutput = new QAudioOutput();
    music->setAudioOutput(audioOutput);
    music->setSource(QUrl("qrc:/audio/resources/theme_OP.mp3"));
    music->play();
}


void Game::freezeGame(){
    obstacleTimer->stop();
    collisionT->stop();
    player->freezeInPlace();
    QList<QGraphicsItem*> sceneItems = items();
    /*for (auto item:sceneItems){
        Obstacle* obst = dynamic_cast<Obstacle*>(item);
        if (obst){
            obst->freezeInPlace();
        }
    }*/     // Alternative method by using std::for_each with a functor FreezeObstacles() :

    std::for_each(sceneItems.begin(), sceneItems.end(), FreezeObstacles());

    hud->stopTimer();

}


void Game::saveScore(int score){
    QFile file("scores.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)){
        QMessageBox::critical(nullptr, "Error", "Error opening scores file");
        return;
    }
    QTextStream out(&file);
    out << score << Qt::endl;
    file.close();
}


void Game::checkHighScore(int score){
    QFile file("scores.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::critical(nullptr, "Error", "Error opening scores file");
        return;
    }
    QTextStream in(&file);
    int highScore = 0;
    int tempScore;
    while (!in.atEnd()){
        in >> tempScore;
        if (tempScore > highScore){
            highScore = tempScore;
        }
    }
    file.close();

    if (score > highScore){
        QMessageBox::information(nullptr, "Congratulations", "You have reached a new high score!");
    }
    else{
        highScoreLabel = new QGraphicsTextItem;
        highScoreLabel->setDefaultTextColor(Qt::black);
        highScoreLabel->setFont(QFont("times",15));
        highScoreLabel->setPlainText(QString("Highscore: ")+QString::number(highScore));
        highScoreLabel->setPos(310,160);
        scene->addItem(highScoreLabel);
    }
}


void Game::gameOver(){
    player->updateCollisionCont();
    for (auto collidedItem:player->collidingItemsContainer){
        if (typeid(*(collidedItem)) == typeid(Obstacle)){
            freezeGame();
            music->stop();
            delete music;
            music = new QMediaPlayer();
            delete audioOutput;
            audioOutput = new QAudioOutput();
            music->setAudioOutput(audioOutput);
            music->setSource(QUrl("qrc:/audio/resources/gameover.mp3"));
            music->play();

            auto currentScore = hud->getScore();

            // displaying a game over text label
            gameOverLabel = new QGraphicsTextItem;
            gameOverLabel->setDefaultTextColor(Qt::red);
            gameOverLabel->setFont(QFont("times",30));
            gameOverLabel->setPlainText(QString("GAME OVER! Your score: ")+QString::number(currentScore));
            gameOverLabel->setPos(130,100);
            scene->addItem(gameOverLabel);

            checkHighScore(currentScore);
            saveScore(currentScore);

            //adding a play again button and connecting its click to the newGame() function
            playAgainB = new QPushButton(nullptr);
            playAgainB->setText("New Game");
            playAgainB->move(330, 200);
            playAgainB->setFixedSize(100, 50);
            QFont font("Arial", 12);
            playAgainB->setFont(font);
            playAgainWidget = new QGraphicsProxyWidget();
            playAgainWidget->setWidget(playAgainB);
            scene->addItem(playAgainWidget);
            connect(playAgainB, &QPushButton::clicked, this, &Game::newGame);

        }
    }

}


void Game::newGame(){
    // removing and deleting unnecessary items
    scene->removeItem(hud);
    delete hud;
    scene->removeItem(gameOverLabel);
    delete gameOverLabel;
    scene->removeItem(playAgainWidget);
    QList<QGraphicsItem*> sceneItems = items();
    if (sceneItems.contains(highScoreLabel)){
        scene->removeItem(highScoreLabel);
        delete highScoreLabel;
    }
    /*for (auto item:sceneItems){
        Obstacle* obst = dynamic_cast<Obstacle*>(item);
        if (obst){
            delete obst;
        }
    }*/     // method replaced with std::for_each() :

    std::for_each(sceneItems.begin(), sceneItems.end(), [](QGraphicsItem* item) {
        Obstacle* obst = dynamic_cast<Obstacle*>(item);
        if (obst) {
            delete obst;
        }
    });

    delete music;
    delete audioOutput;

    // restarting game
    playMusic();
    setUpObstacleTimer();
    collisionT->start();
    player->unfreeze();

    player->setFocus();
    hud = new HUD();
    scene->addItem(hud);
}

//! \endcode
