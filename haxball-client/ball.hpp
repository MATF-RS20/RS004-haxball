#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>


class Ball : public QGraphicsEllipseItem
{
public:
    Ball() = default;
    Ball(const qreal x, const qreal y,
         const qreal diameter = 20,
         const QColor& circleColor = QColor(Qt::blue),
         const QColor& circularColor = QColor(Qt::white),
         const int circularWidth = 3);
};

#endif // BALL_H
