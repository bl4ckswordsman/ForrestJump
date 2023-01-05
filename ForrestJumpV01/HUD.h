#ifndef HUD_H
#define HUD_H

#include <QGraphicsTextItem>
#include <QTimer>

class HUD : public QGraphicsTextItem{
Q_OBJECT
public:
    HUD(QGraphicsItem* parent=nullptr);
    //~HUD();
    int getScore() const;
    void stopTimer();

public slots:
    void scoreIncrement();
private:
    int score;
    QTimer* HUDTimer;
};

#endif // HUD_H
