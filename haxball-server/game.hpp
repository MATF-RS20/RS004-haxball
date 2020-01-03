#ifndef GAME_HPP
#define GAME_HPP

#include <QObject>

#include <utility>
#include <map>
#include <vector>

#include <ctime>

#include "player.hpp"

class Game
{

public:
  explicit Game(unsigned players_number = 10,
             time_t id = time(nullptr),
             std::pair<unsigned, unsigned> result = std::make_pair<unsigned, unsigned>(0,0));

private:
  time_t m_id;
  std::pair<unsigned, unsigned> m_result;
  unsigned m_players_number;
  std::vector<Player> m_players;

};

#endif // GAME_HPP
