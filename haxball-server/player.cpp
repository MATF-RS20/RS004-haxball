#include "player.hpp"

#include <QLocale>
#include <QString>

Player::Player(qintptr id, std::string name, double x0, double y0)
  : m_id(id),m_x0(x0), m_y0(y0), m_name(name)
{ }

std::string Player::name() const
{
  return m_name;
}

qintptr Player::id() const
{
  return m_id;
}

void Player::x_y(double x, double y)
{
  m_x0 = x;
  m_y0 = y;
}


QString Player::toString() const
{

  QString s =  " " + QString::number(m_id)
                  + " " + QString::number(m_x0)
                  + " " + QString::number(m_y0) + "\n" ;
  return s;
}


