/* DT079G Project - Forrest Jump game
 *  Amarildo Rajta 2023-01-07 */
#ifndef HUD_H
#define HUD_H

#include <QGraphicsTextItem>
#include <QTimer>

/*!
 * \brief The HUD(Heads Up Display) class
 */
class HUD : public QGraphicsTextItem{
Q_OBJECT
public:
    /*!
     * \brief The HUD class constructor
     * \param parent The QGraphicsItem to use as a parent class, defaulted to nullptr
     */
    HUD(QGraphicsItem* parent = nullptr);
    /*!
     * \brief Gets the current score
     * \return The current score (int)
     */
    int getScore() const;
    /*!
     * \brief Stops the timer on which the score is based on
     */
    void stopTimer();


private:
    /*!
     * \brief The current score (int)
     */
    int score;
    /*!
     * \brief The QTimer that will be connected to the scoreIncrement function
     */
    QTimer* HUDTimer;
private slots:
    /*!
     * \brief Increments the score by 1
     */
    void scoreIncrement();
};

#endif // HUD_H
