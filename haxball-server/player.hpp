#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QObject>


class Player
{

public:

  Player() = default;

  explicit Player(qintptr id, std::string name, long x0 = 0, long y0 = 0);

  std::string toString() const;

  std::string name() const;

  qintptr id() const;

  void x_y(long x, long y);


private:
  qintptr m_id;
  long m_x0, m_y0;

  std::string  m_name;

};

#endif // PLAYER_HPP
