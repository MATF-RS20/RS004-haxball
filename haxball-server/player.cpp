#include "player.hpp"

Player::Player(qintptr id, std::string name, float x0, float y0, float x1, float y1)
  : m_id(id), m_name(name)
{ }

std::string Player::name() const
{
  return m_name;
}


std::string Player::toString() const
{
//  std::string s =  std::to_string(m_id)
//                  + " " + m_name
//                  + " " + std::to_string(x0)
//                  + " " + std::to_string(y0)
//                  + " " + std::to_string(x1)
//                  + " " + std::to_string(y1);


  std::string s =  " " + std::to_string(m_id)
                  + " " + std::to_string(x1)
                  + " " + std::to_string(y1);
  return s;
}


