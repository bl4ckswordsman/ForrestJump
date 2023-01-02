#ifndef HUD_H
#define HUD_H

#include <QGraphicsTextItem>

class HUD : public QGraphicsTextItem{
Q_OBJECT
public:
    HUD(QGraphicsItem* parent=0);
public slots:
    void scoreIncrement();
private:
    int score;
};

#endif // HUD_H
