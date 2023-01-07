/* DT079G Project - Forrest Jump game
 *  Amarildo Rajta 2023-01-07 */
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

/*!
 * \brief The Game class
 * The game class initiates objects from the Player, Obstacle, HUD class, assisted by animation and
 * collision detection methods as well as other image and audio components to run the Forrest Jump
 * game.
 */
class Game : public QGraphicsView{
Q_OBJECT
public:
    /*!
     * \brief The Game class constructor
     * \param parent The QWidget to use as a parent class, defaulted to nullptr
     */
    Game(QWidget* parent = nullptr);


private:
    /*!
     * \brief Initializes class members and configures core function of the game
     */
    void initiateGameElements();
    /*!
     * \brief Configures the 'obstacleTimer' and connects it to creation of Obstacle objects
     */
    void setUpObstacleTimer();
    /*!
     * \brief Plays the game background music stored in the qrc file component
     */
    void playMusic();
    /*!
     * \brief Freezes the player and obstacles in place as well as stops timers
     */
    void freezeGame();
    /*!
     * \brief Saves the score in "scores.txt" and displays a QMessageBox if it fails
     * \param score The score to be saved
     */
    void saveScore(int score);
    /*!
     * \brief Checks for high score in "scores.txt", compares it to user score and displays relevant information
     * \param score The score to be compared to the highest score
     */
    void checkHighScore(int score);
    /*!
     * \brief Game scene width
     */
    const int xSize = 800;
    /*!
     * \brief Game scene height
     */
    const int ySize = 600;

    /*!
     * \brief QTimer that will be connected to obstacle creation
     */
    QTimer* obstacleTimer;
    /*!
     * \brief QTimer that will be connected to collision detection
     */
    QTimer* collisionT;

    /*!
     * \brief The scene the all the game elements will reside in
     */
    QGraphicsScene* scene;
    /*!
     * \brief The background pixmap
     */
    QGraphicsPixmapItem* bg;
    /*!
     * \brief The player
     */
    Player* player;
    /*!
     * \brief The heads up display that contains the score
     */
    HUD* hud;
    /*!
     * \brief The audio output device
     */
    QAudioOutput* audioOutput;
    /*!
     * \brief The music player device
     */
    QMediaPlayer* music;

    /*!
     * \brief The game over text label that will also show the score
     */
    QGraphicsTextItem* gameOverLabel;
    /*!
     * \brief The text label that will show the highest score registered
     */
    QGraphicsTextItem* highScoreLabel;
    /*!
     * \brief The 'Play Again' button
     */
    QPushButton* playAgainB;
    /*!
     * \brief The 'Play Again' widget proxy needed for the button
     */
    QGraphicsProxyWidget* playAgainWidget;
private slots:
    /*!
     * \brief Shows endgame information if it detects player-obstacle collisions
     */
    void gameOver();
    /*!
     * \brief Starts a new game by deleting 'game over' objects and reconfiguring game components
     */
    void newGame();
};

#endif // GAME_H
