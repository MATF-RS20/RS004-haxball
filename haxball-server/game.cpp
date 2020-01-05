#include "game.hpp"

#include <ctime>

Game::Game(unsigned players_number, time_t id, std::pair<unsigned, unsigned> result)
  :m_players_number(players_number), m_id(id), m_result(result)
  {}


void Game::addPlayer(Player & player)
{
  m_players.push_back(player);
}


std::string Game::toString() const
{
//  std::string s =  " gameId:" + std::to_string(m_id) +
//            " players_number:" + std::to_string(m_players_number) +
//            " result:" + std::to_string(m_result.first) + ":" + std::to_string(m_result.second) +
//            " ";

    std::string s =  " " + std::to_string(m_id) +
              " " + std::to_string(m_players_number) +
              " " + std::to_string(m_result.first) + ":" + std::to_string(m_result.second) +
              " ";

  std::string players;
  for(auto iter = std::begin(m_players); iter != m_players.end(); iter++)
  {
    players.append(iter->toString());
    players.append(" ");
  }

  s.append(players);

  return s;
}


