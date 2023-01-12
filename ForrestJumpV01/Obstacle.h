/*! \author Amarildo Rajta \date 2023-01-07
 *  \details DT079G Project - Forrest Jump game */
//! \headerfile Obstacle.h
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QGraphicsScene>

/*!
 * \brief The Obstacle class
 */
class Obstacle : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    /*!
     * \brief The Obstacle class constructor
     * \param parent The QGraphicsItem to use as a parent class, defaulted to nullptr
     */
    explicit Obstacle(QGraphicsItem* parent = nullptr);
    //~Obstacle();

    /*!
     * \brief Stops the horizontal movement/animation
     */
    void freezeInPlace();
    /*!
     * \brief Starts the horizontal movement/animation
     */
    void startAnimation();
private:
    /*!
     * \brief The horizontal animation
     */
    QPropertyAnimation* xAnimation;
private slots:
    /*!
     * \brief Sets the x coordinate of the object
     * \param x The horizontal position for the object to be set to
     */
    void setX(qreal x);
};

#endif // OBSTACLE_H
