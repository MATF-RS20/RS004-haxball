#include "game.hpp"

#include <ctime>
#include <QString>

Game::Game(std::string name, unsigned players_number, std::string id,  std::pair<unsigned, unsigned> result)
  :m_name(name), m_id(id), m_players_number(players_number), m_result(result)
  { }

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

    return { x0 + (rand() % (x1 - x0)), y0 + (rand() % (y1 - y0)) };
}


QString Game::toString() const
{
    QString s =   " " + QString::fromStdString(m_name)
                    + " " + QString::fromStdString(m_id)
                    + " " + QString::number(m_players_number)
                    + " " + QString::number(m_result.first) + ":" + QString::number(m_result.second);

  return s;
}

QString Game::print_game()
{
  QString s =   " " + QString::fromStdString(m_name)
                  + " " + QString::fromStdString(m_id)
                  + " " + QString::number(m_players_number)
                  + " " + QString::number(m_result.first) + ":" + QString::number(m_result.second);

    for(auto iter  = m_players.begin() ; iter != m_players.end() ; iter++)
      {
        s += iter->toString();
        s += " ";
      }

  return s;
}

std::vector<Player> & Game::players()
{
  return m_players;
}


