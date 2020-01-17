#include "player.hpp"

#include <QLocale>
#include <QString>

Player::Player(qintptr id, std::string name, double x0, double y0)
  : m_id(id),m_x0(x0), m_y0(y0), m_name(name)
{ }

Player::Player(const Player & other)
{
  this->m_id = other.m_id;
  this->m_name = other.m_name;
  this->m_x0 = other.m_x0;
  this->m_y0 = other.m_y0;
}

Player & Player::operator= (const Player & other)
{
  Player tmp(other);

  std::swap(m_id, tmp.m_id);
  std::swap(m_name, tmp.m_name);
  std::swap(m_x0, tmp.m_x0);
  std::swap(m_y0, tmp.m_y0);

  return *this;
}

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


