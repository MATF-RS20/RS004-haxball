#include "player.hpp"
#include <QKeyEvent>
#include "clientsocket.hpp"
#include <iostream>

Player::Player(const qreal x, const qreal y, const qreal diameter, const QColor& circleColor, const QColor& circularColor, const int circularWidth)
    : QGraphicsEllipseItem(x, y, diameter, diameter)
{
    setBrush(circleColor);
    setPen(QPen(circularColor, circularWidth, Qt::SolidLine));
}



void Player::draw(QGraphicsScene *scene)
{
    scene->addItem(this);
}



/* ============================= KOMSA =============================

const char* Player::actionToString(Actions a)
{

    switch (a) {
        case key_left: return "key_left";
        case key_right: return "key_right";
        case key_up: return "key_up";
        case key_down: return "key_down";
        case shot: return "shot";
    default:
        throw "Nepoznat taster.";
    }
}

void Player::keyPressEvent(QKeyEvent *event){


    auto conn = ClientSocket::instance(QHostAddress::LocalHost, 3333);
    auto socket = conn.get()->getSocket();

    const char* str;
    if (event->key() == Qt::Key_Left){
        str = actionToString(key_left);
        socket->write(str);

        if(x() > -m_x)
        {
            setPos(x()-5, y());
        }
    }
    else if (event->key() == Qt::Key_Right){
        str = actionToString(key_right);
        socket->write(str);

        if(x() < 960-m_x)
        {
            setPos(x()+5, y());
        }
    }
    else if (event->key() == Qt::Key_Up){
        str = actionToString(key_up);
        socket->write(str);

        if(y() > -m_y)
        {
            setPos(x(), y()-5);
        }
    }
    else if (event->key() == Qt::Key_Down){
        str = actionToString(key_down);
        socket->write(str);

        if(y() < 460-m_y)
        {
            setPos(x(), y()+5);
        }
    }
    else if (event->key() == Qt::Key_Space) {
        str = actionToString(shot);
        socket->write(str);
    }
    emit socket->bytesWritten(sizeof (str));
    socket->flush();

}

Player* Player::drawPlayer(int x, int y)
{

    setX(x);
    setY(y);
    player->setRect(x, y, 40, 40);
    player->setStartAngle(0);
    player->setSpanAngle(360*16);
    player->setBrush(Qt::red);
    QPen pen;
    pen.setWidth(2);
    player->setPen(pen);
    return player;

}

*/
