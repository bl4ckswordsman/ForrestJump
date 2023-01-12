/*! \author Amarildo Rajta \date 2023-01-07
 *  \details DT079G Project - Forrest Jump game */
//! \headerfile Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QProperty>
#include <QPropertyAnimation>
#include <QMediaPlayer>
#include <QAudioOutput>

/*!
 * \brief The Player class
 */
class Player : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    /*!
     * \brief The Player class constructor
     * \param parent The QGraphicsItem to use as a parent class, defaulted to nullptr
     */
    Player(QGraphicsItem *parent = nullptr);

    /*!
     * \brief Stops the vertical animation and sets jumpAllowed to false
     */
    void freezeInPlace();
    /*!
     * \brief Starts the vertical animation and sets jumpAllowed to true
     */
    void unfreeze();

    /*!
     * \brief Sets the y coordinate of the object
     * \param Y The vertical position for the object to be set to
     */
    void setY(qreal Y);

    /*!
     * \brief Finds out at what y coordinate the object is at
     * \return The current y coordinate of the object
     */
    qreal y() const;

    /*!
     * \brief Stores all the items that Player has collided with
     */
    QList<QGraphicsItem*> collidingItemsContainer;
    /*!
     * \brief Stores if jumps are allowed, i.e. when the game is running
     */
    bool jumpsAllowed;
public slots:
    /*!
     * \brief Updates the collidingItemsContainer with a current list of colliding items
     */
    void updateCollisionCont();
private:
    /*!
     * \brief Takes keyboard user input to perform jumps
     * \param event The keyboard key pressed
     */
    void keyPressEvent(QKeyEvent *event);
    /*!
     * \brief Performs the 'jumping up' animation
     */
    void jump();
    /*!
     * \brief The QPropertyAnimation that will be configured for the player jump
     */
    QPropertyAnimation* jumpAnimation;

    /*!
     * \brief Returns true if the player is jumping, false otherwise.
     * Needed to prevent double jumping.
     */
    bool isJumping;
    /*!
     * \brief The jumping sound effect
     */
    QMediaPlayer* jumpSFX;
    /*!
     * \brief The jumping sound audio output device
     */
    QAudioOutput* audioOutputJ;
private slots:
    /*!
     * \brief Initiates the falling down animation
     */
    void fallDown();
    /*!
     * \brief Allows the player to jump again and disconnects the falling down animation
     */
    void jumpFinished();

};

#endif // PLAYER_H
