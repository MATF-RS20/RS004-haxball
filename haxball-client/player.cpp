#include "player.h"
#include <QKeyEvent>
#include "clientsocket.hpp"
#include <iostream>

Player::Player()
    : player(this)
{}

//enum Actions {
//   key_left,
//   key_right,
//   key_up,
//   key_down,
//   shot
//};

//const std::string actionToString(Actions a)
//{
//    switch (a) {
//        case key_left: return "key_left";
//        case key_right: return "key_right";
//        case key_up: return "key_up";
//        case key_down: return "key_down";
//        case shot: return "shot";
//    }
//}

void Player::keyPressEvent(QKeyEvent *event){

    auto conn = ClientSocket::instance(QHostAddress::LocalHost, 3333);
    auto socket = conn.get()->getSocket();

    if (event->key() == Qt::Key_Left){  
        socket->write("key_left");

        if(x() > -player_x)
        {
            setPos(x()-5, y());
        }
    }
    else if (event->key() == Qt::Key_Right){
        socket->write("key_right");

        if(x() < 960-player_x)
        {
            setPos(x()+5, y());
        }
    }
    else if (event->key() == Qt::Key_Up){
        socket->write("key_up");

        if(y() > -player_y)
        {
            setPos(x(), y()-5);
        }
    }
    else if (event->key() == Qt::Key_Down){
        socket->write("key_down");

        if(y() < 460-player_y)
        {
            setPos(x(), y()+5);
        }
    }
    emit socket->bytesWritten(100);
}

Player* Player::drawPlayer(int x, int y)
{
    set_playerX(x);
    set_playerY(y);
    player->setRect(x, y, 40, 40);
    player->setStartAngle(0);
    player->setSpanAngle(360*16);
    player->setBrush(Qt::red);
    QPen pen;
    pen.setWidth(2);
    player->setPen(pen);
    return player;
}

void Player::set_playerX(int x)
{
    player_x = x;
}

void Player::set_playerY(int y)
{
    player_y = y;
}
