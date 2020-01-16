#include "ball.hpp"
#include <QPen>

Ball::Ball(const qreal x, const qreal y, const qreal diameter, const QColor& circleColor, const QColor& circularColor, const int circularWidth)
    : QGraphicsEllipseItem(x, y, diameter, diameter)
{
    setBrush(circleColor);
    setPen(QPen(circularColor, circularWidth, Qt::SolidLine));
}
