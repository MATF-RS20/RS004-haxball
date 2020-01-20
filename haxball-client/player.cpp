#include "player.hpp"
#include <QKeyEvent>
#include "clientsocket.hpp"
#include <iostream>

const qreal Player::MAX_SPEED = 5;
const qreal Player::ACCELERATION = 0.3;
const qreal Player::SLOWING = 0.1;


Player::Player(const qreal x, const qreal y, const int team, const qreal diameter, const QColor& circleColor, const QColor& circularColor, const int circularWidth)
    : QGraphicsEllipseItem(x, y, diameter, diameter)
{
    if(team == 1){
      setBrush(QColor(Qt::red));
    }
    else if(team == 0){
        setBrush(QColor(Qt::black));
      }
    else{
        setBrush(circleColor);
      }
    setPen(QPen(circularColor, circularWidth, Qt::SolidLine));

}

int Player::getId() const
{
    return m_id;
}

void Player::setId(int value)
{
    m_id = value;
}

void Player::accelerateX(qreal acc)
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

void Player::accelerateY(qreal acc)
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

void Player::slow(qreal s)
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

qreal Player::getSpeedY() const
{
    return m_speedY;
}

qreal Player::getSpeedX() const
{
    return m_speedX;
}


