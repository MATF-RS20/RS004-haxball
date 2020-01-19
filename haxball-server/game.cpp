#include "game.hpp"

#include <ctime>
#include <QString>
#include <memory>

Game::Game(std::string name, unsigned players_number, std::string id,  std::pair<unsigned, unsigned> result)
  :m_name(name), m_id(id), m_players_number(players_number), m_result(result)
{ }

Game::Game(const Game & other)
{

  this->m_name = other.m_name;
  this->m_players_number = other.m_players_number;
  this->m_id = other.m_id;
  this->m_result = other.m_result;

  //   std::vector<std::unique_ptr<Player>> m_players;
  for(auto iter = std::begin(other.m_players) ; iter != std::end(other.m_players) ; iter++)
    {
      auto player_ptr = std::make_unique<Player>(**iter);
      this->m_players.push_back(std::move(player_ptr));
    }
}

Game & Game::operator=(const Game & other)
{

  Game tmp(other);

  std::swap(m_name, tmp.m_name);
  std::swap(m_players_number, tmp.m_players_number);
  std::swap(m_id, tmp.m_id);
  std::swap(m_result, tmp.m_result);
  std::swap(m_players, tmp.m_players);

  return *this;
}

Game::Game(Game && other) noexcept
  : m_name(other.m_name)
  , m_id(other.m_id)
  , m_players_number(other.m_players_number)
  , m_result(other.m_result)
{

  for(auto iter = std::begin(other.m_players) ; iter != std::end(other.m_players) ; iter++)
    {
      auto player_ptr = std::make_unique<Player>(*iter);
      this->m_players.push_back(std::move(player_ptr));
    }

  other.m_name = "";
  other.m_players_number = 0;
  other.m_id = "";
  other.m_result = {-1,-1};

}

Game & Game::operator=(Game && other) noexcept
{

  this->m_name = other.m_name;
  this->m_players_number = other.m_players_number;
  this->m_id = other.m_id;
  this->m_result = other.m_result;

  for(auto iter = std::begin(other.m_players) ; iter != std::end(other.m_players) ; iter++)
    {
      auto player_ptr = std::make_unique<Player>(*iter);
      this->m_players.push_back(std::move(player_ptr));
    }

  other.m_name = "";
  other.m_players_number = 0;
  other.m_id = "";
  other.m_result = {-1,-1};

  return *this;
}


std::string  Game::gameId() const
{
  return m_id;
}

std::string Game::name() const
{
  return m_name;
}

unsigned Game::playersNumber() const
{
  return m_players_number;
}

void Game::addPlayer(std::unique_ptr<Player> && player_ptr)
{
  //  auto p = randomPosition();
  //  player_ptr->setXY(p.first, p.second);

  m_players.push_back(std::move(player_ptr));
}


//std::pair<long, long> Game::randomPosition() const
//{
//    auto x0 = mbbox.first.first;
//    auto y0 = mbbox.first.second;
//    auto x1 = mbbox.second.first;
//    auto y1 = mbbox.second.second;

//    return { x0 + (rand() % (x1 - x0)), y0 + (rand() % (y1 - y0)) };
//}


QString Game::toSocketString() const
{
  QString s =   " " + QString::fromStdString(m_name)
      + " " + QString::fromStdString(m_id)
      + " " + QString::number(m_players_number)
      + " " + QString::number(m_result.first) + ":" + QString::number(m_result.second) + "\n";

  return s;
}

QString Game::toString() const
{
  QString s =   " " + QString::fromStdString(m_name)
      + " " + QString::fromStdString(m_id)
      + " " + QString::number(m_players_number)
      + " " + QString::number(m_result.first) + ":" + QString::number(m_result.second);

  for(auto iter  = m_players.begin() ; iter != m_players.end() ; iter++)
    {
      s += (*iter)->toString();
      s += " ";
    }

  return s;
}


std::vector<std::shared_ptr<Player>> & Game::players()
{
  return m_players;
}


