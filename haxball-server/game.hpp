#ifndef GAME_HPP
#define GAME_HPP

#include <QObject>

#include <utility>
#include <map>
#include <vector>

#include <ctime>

#include <iostream>

#include "player.hpp"

class Game
{

public:

  Game() = default;

  explicit Game(std::string name, unsigned players_number = 10, std::string id = std::to_string(time(nullptr)),
                std::pair<unsigned, unsigned> result = std::make_pair<unsigned, unsigned>(0,0));

  std::string & gameId() ;

  void addPlayer(Player & player);

  std::string toString() const;

private:
  std::string m_name;
  std::string m_id;
  unsigned m_players_number;
  std::pair<unsigned, unsigned> m_result;

  std::vector<Player> m_players;
};


#endif // GAME_HPP
