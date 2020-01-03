#include "player.h"
#include <QKeyEvent>

Player::Player()
    : player(this)
{}

void Player::keyPressEvent(QKeyEvent *event){

    if (event->key() == Qt::Key_Left){
        if(x() > -player_x)
        {
            setPos(x()-5, y());
        }
    }
    else if (event->key() == Qt::Key_Right){
        if(x() < 960-player_x)
        {
            setPos(x()+5, y());
        }
    }
    else if (event->key() == Qt::Key_Up){
        if(y() > -player_y)
        {
            setPos(x(), y()-5);
        }
    }
    else if (event->key() == Qt::Key_Down){
        if(y() < 460-player_y)
        {
            setPos(x(), y()+5);
        }
    }
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
