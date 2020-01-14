#include "game.hpp"

#include <ctime>

Game::Game(std::string name, std::string id, unsigned players_number,  std::pair<unsigned, unsigned> result)
  :m_name(name), m_id(id), m_players_number(players_number), m_result(result)
  {}

std::string & Game::gameId()
{
  return m_id;
}

void Game::addPlayer(Player & player)
{
  m_players.push_back(player);
}


std::string Game::toString() const
{

    std::string s =   " " + m_name
                    + " " + m_id
                    + " " + std::to_string(m_players_number)
                    + " " + std::to_string(m_result.first) + ":" + std::to_string(m_result.second)
                    + " ";

  std::string players;
  for(auto iter = std::begin(m_players); iter != m_players.end(); iter++)
  {
    players.append(iter->toString());
    players.append(" ");
  }

  s.append(players);

  return s;
}


