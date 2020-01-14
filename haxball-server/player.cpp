#include "player.hpp"

Player::Player(qintptr id, std::string name, std::string surname, float x0, float y0, float x1, float y1)
  : m_id(id), m_name(name), m_surname(surname)
{ }

std::string Player::name() const
{
  return m_name;
}

std::string  Player::surname() const
{
  return m_surname;
}

std::string Player::toString() const
{
  std::string s =  std::to_string(m_id)
                  + " " + m_name
                  + " " + m_surname
                  + " " + std::to_string(x0)
                  + " " + std::to_string(y0)
                  + " " + std::to_string(x1)
                  + " " + std::to_string(y1);

  return s;
}


