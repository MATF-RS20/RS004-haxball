#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QObject>


class Player : public QObject
{

  Q_OBJECT

public:
  Player();


private:
  qintptr m_id;
  float x0, y0, x1, y1;

};

#endif // PLAYER_HPP
