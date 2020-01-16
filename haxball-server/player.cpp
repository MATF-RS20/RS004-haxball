#include "player.hpp"

Player::Player(qintptr id, std::string name, long x0, long y0)
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

void Player::x_y(long x, long y)
{
  m_x0 = x;
  m_y0 = y;
}


std::string Player::toString() const
{

  std::string s =  " " + std::to_string(m_id)
                  + " " + std::to_string(m_x0)
                  + " " + std::to_string(m_y0);
  return s;
}


