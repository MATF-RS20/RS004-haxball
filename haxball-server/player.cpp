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
  std::string s =  "id:" + std::to_string(m_id) +
            " name: " + name() +
            " surname: " + surname() +
            " x0:" + std::to_string(x0) +
            " y0:" + std::to_string(y0) +
            " x1:" + std::to_string(x1) +
            " y1:" + std::to_string(y1);

  return s;
}


