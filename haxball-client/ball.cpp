#include "ball.hpp"
#include <QPen>

const qreal Ball::MAX_SPEED = 5;
const qreal Ball::ACCELERATION = 0.5;
const qreal Ball::SLOWING = 0.1;

Ball::Ball(const qreal x, const qreal y, const qreal diameter, const QColor& circleColor, const QColor& circularColor, const int circularWidth)
    : QGraphicsEllipseItem(x, y, diameter, diameter)
{
    setBrush(circleColor);
    setPen(QPen(circularColor, circularWidth, Qt::SolidLine));
}

void Ball::accelerateX(qreal acc)
{
    m_speedX += acc;

    if(this->y() > 175 && this->y() < 285) {
        if(this->x() < -50){
            m_speedX = MAX_SPEED;
        }
        if(this->x() > 1000) {
            m_speedX = -MAX_SPEED;
        }
    }
    else {
        if(this->x() < 0) {
            m_speedX = MAX_SPEED;
        }
        if(this->x() > 960) {
            m_speedX = -MAX_SPEED;
        }
    }

    if(m_speedX > MAX_SPEED)
        m_speedX = MAX_SPEED;

    else if(m_speedX < -MAX_SPEED)
        m_speedX = -MAX_SPEED;
}

void Ball::accelerateY(qreal acc)
{
    m_speedY += acc;

    if(this->x() < 0 || this->x() > 1000){
        if(this->y() < 175) {
            m_speedY = MAX_SPEED;
        }
        if (this->y() > 285) {
            m_speedY = -MAX_SPEED;
        }
    }

    if(this->y() < 0) {
        m_speedY = MAX_SPEED;
    }

    if(this->y()  > 460) {
        m_speedY = -MAX_SPEED;
    }

    if(m_speedY > MAX_SPEED){
        m_speedY = MAX_SPEED;
    }
    else if(m_speedY < -MAX_SPEED)
        m_speedY = -MAX_SPEED;
}

void Ball::slow(qreal s)
{

    if(m_speedX < -s){
        m_speedX += s;
    }
    else if(m_speedX < 0){
        m_speedX = 0;
    }
    else if(m_speedX > s){
        m_speedX -= s;
    }
    else if(m_speedX < s){
        m_speedX = 0;
    }


    if(this->y() < 0 || this->y()  > 460) {
        m_speedY = 0;
    }

    if(m_speedY < -s){
        m_speedY += s;
    }
    else if(m_speedY < 0){
        m_speedY = 0;
    }
    else if(m_speedY > s){
        m_speedY -= s;
    }
    else if(m_speedY < s){
        m_speedY = 0;
    }

    if(this->y() > 175 && this->y() < 285) {
        if(this->x() < -50 || this->x() > 1000){
            m_speedX = 0;
        }
    }
    else {
            if(this->x() < 0 || this->x() > 960) {
                m_speedX = 0;
            }
    }

}

void Ball::setSpeedX(const qreal &speedX)
{
    m_speedX = speedX;
}

void Ball::setSpeedY(const qreal &speedY)
{
    m_speedY = speedY;
}

qreal Ball::getSpeedY() const
{
    return m_speedY;
}

/*qreal Ball::setSpeedX(qreal x)
{
    m_speedX = x;
}

qreal Ball::setSpeedY(qreal y)
{
    m_speedY = y;
}*/

qreal Ball::getSpeedX() const
{
    return m_speedX;
}
