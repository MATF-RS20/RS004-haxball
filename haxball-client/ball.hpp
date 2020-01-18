#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>


class Ball : public QGraphicsEllipseItem
{
public:
    Ball() = default;
    Ball(const qreal x, const qreal y,
         const qreal diameter = 40,
         const QColor& circleColor = QColor(Qt::blue),
         const QColor& circularColor = QColor(Qt::white),
         const int circularWidth = 3);


    qreal getSpeedX() const;
    qreal getSpeedY() const;

    void accelerateX(qreal acc);
    void accelerateY(qreal acc);
    void slow(qreal s);

    static const qreal MAX_SPEED;
    static const qreal ACCELERATION;
    static const qreal SLOWING;

private:
    qreal m_speedX = 0;
    qreal m_speedY = 0;

};

#endif // BALL_H
