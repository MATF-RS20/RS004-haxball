#ifndef GAME_HPP
#define GAME_HPP

#include <QObject>

#include <utility>
#include <map>
#include <vector>

#include <ctime>

#include "player.hpp"

class Game : public QObject
{

  Q_OBJECT

public:

  Game();


private:
  time_t m_id;
  std::pair<unsigned, unsigned> m_result;
  unsigned m_players_number;
  std::vector<Player> m_players;

};

#endif // GAME_HPP
