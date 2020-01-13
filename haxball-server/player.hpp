#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QObject>


class Player
{

public:
  explicit Player(qintptr id, std::string name, std::string surname, float x0 = 0, float y0 = 0, float x1 = 0, float y1 = 0);

  std::string toString() const;

  std::string name() const;

  std::string surname() const;


private:
  qintptr m_id;
  float x0, y0, x1, y1;

  std::string  m_name, m_surname;

};

#endif // PLAYER_HPP
