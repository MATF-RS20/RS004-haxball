#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QObject>


class Player
{

public:
  explicit Player(qintptr id, float x0 = 0, float y0 = 0, float x1 = 0, float y1 = 0);

  std::string toString() const;

private:
  qintptr m_id;
  float x0, y0, x1, y1;

};

#endif // PLAYER_HPP
