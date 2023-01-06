#include "Game.h"
#include "Obstacle.h"
#include <QPropertyAnimation>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QFont>
#include <QGraphicsPixmapItem>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>


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

    // adding background image
    bg = new QGraphicsPixmapItem();
    bg->setPixmap(QPixmap(":/images/resources/bg.png"));
    bg->setPos(0,0);
    //bg->setZValue(-1);
    //bg->setFlag(QGraphicsItem::ItemIsFocusable);
    //bg->setFocus();
    scene->addItem(bg);

    // creating the player
    player = new Player();
    player->jumpsAllowed = true;
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
        qDebug() << "New HIGHSCORE";
        QMessageBox::information(nullptr, "Congratulations", "You have reached a new high score!");
    }
}

void Game::gameOver(){

    player->updateCollisionCont();
    for (auto collidedItem:player->collidingItemsContainer){
        if (typeid(*(collidedItem)) == typeid(Obstacle)){
            freezeGame();
            music->stop();
            music = new QMediaPlayer();
            QAudioOutput* audioOutput2 = new QAudioOutput();
            music->setAudioOutput(audioOutput2);
            music->setSource(QUrl("qrc:/audio/resources/gameover.mp3"));
            music->play();
            auto currentScore = hud->getScore();
            this->disconnect();




            auto gameOVER = new QGraphicsTextItem;
            gameOVER->setDefaultTextColor(Qt::red);
            gameOVER->setFont(QFont("times",30));
            gameOVER->setPlainText(QString("GAME OVER! Your score: ")+QString::number(currentScore));
            gameOVER->setPos(130,100);
            scene->addItem(gameOVER);
            checkHighScore(currentScore);
            saveScore(currentScore);

            auto playAgainB = new QPushButton(nullptr);
            playAgainB->setText("New Game");
            playAgainB->move(330, 200);
            playAgainB->setFixedSize(100, 50);
            QFont font("Arial", 12);
            playAgainB->setFont(font);
            scene->addWidget(playAgainB);
            connect(playAgainB, &QPushButton::clicked, this, &Game::newGame);

        }
    }

    //disconnect
}

void Game::newGame(){
    /*scene->clear();
    delete this->player;
    this->player = new Player();

    this->hud = new HUD();*/
    delete this->hud;
    //scene->clear();
    initiateGameElements();
}
