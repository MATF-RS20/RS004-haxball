#include "game.hpp"

#include <ctime>

Game::Game(std::string name, unsigned players_number, std::string id,  std::pair<unsigned, unsigned> result)
  :m_name(name), m_id(id), m_players_number(players_number), m_result(result)
  {}

std::string & Game::gameId()
{
  return m_id;
}

std::string & Game::name()
{
return m_name;
}

unsigned Game::playersNumber()
{
  return m_players_number;
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
                    + " " + std::to_string(m_result.first) + ":" + std::to_string(m_result.second);

//  std::string players;
//  for(auto iter = std::begin(m_players); iter != m_players.end(); iter++)
//  {
//    players.append(iter->toString());
//    players.append(" ");
//  }

//  s.append(players);

  return s;
}

std::vector<Player> & Game::players()
{
  return m_players;
}


