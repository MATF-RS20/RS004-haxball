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

void Game::addPlayer(Player player)
{
  auto p = randomPosition();
  player.x_y(p.first, p.second);

  m_players.push_back(player);
}


std::pair<long, long> Game::randomPosition()
{
    auto x0 = mbbox.first.first;
    auto y0 = mbbox.first.second;
    auto x1 = mbbox.second.first;
    auto y1 = mbbox.second.second;

    return { x0 + (random() % (x1 - x0)), y0 + (random() % (y1 - y0)) };
}


std::string Game::toString() const
{

    std::string s =   " " + m_name
                    + " " + m_id
                    + " " + std::to_string(m_players_number)
                    + " " + std::to_string(m_result.first) + ":" + std::to_string(m_result.second);

  return s;
}

std::vector<Player> & Game::players()
{
  return m_players;
}


