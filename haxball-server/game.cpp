#include "game.hpp"
#include "ball.hpp"

#include <ctime>
#include <QString>
#include <memory>
#include <QtMath>

Game::Game(std::string name, unsigned players_number, std::string id,  std::pair<unsigned, unsigned> result)
  :m_name(name), m_id(id), m_players_number(players_number), m_result(result)
{
  m_ball.setX(480);
  m_ball.setY(230);
}

Game::Game(const Game & other)
{

  this->m_name = other.m_name;
  this->m_players_number = other.m_players_number;
  this->m_id = other.m_id;
  this->m_result = other.m_result;

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

void Game::addPlayer(std::shared_ptr<Player> & player_ptr)
{
  //  auto p = randomPosition();
  //  player_ptr->setXY(p.first, p.second);

  auto n = m_players.size();
  player_ptr->setTeamNo(n % 2);

  m_players.push_back(player_ptr);
}


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



void Game::resolveColision(std::string gameId, double playerX, double playerY, double playerSpeedX, double playerSpeedY, bool isSpacedPressed)
{

  // PROTOCOL:  collision  gameId  playerX  playerY  playerSpeedX  playerSpeedY  isSpacedPressed

  qreal px_cord = playerX + 20 * sqrt(2);
  qreal py_cord = playerY + 20 * sqrt(2);
  qreal bx_cord = m_ball.x() + 20 * sqrt(2);
  qreal by_cord = m_ball.y() + 20 * sqrt(2);

  qreal rastojanje = qSqrt((px_cord - bx_cord)*(px_cord - bx_cord) + (py_cord - by_cord)*(py_cord - by_cord));

  qreal pomeraj = 0.5 * (rastojanje - 20 - 20);
  px_cord -= pomeraj * (px_cord - bx_cord) / rastojanje;
  py_cord -= pomeraj * (py_cord - by_cord) / rastojanje;

  bx_cord += pomeraj * (bx_cord - px_cord) / rastojanje;
  by_cord += pomeraj * (by_cord - py_cord) / rastojanje;

  rastojanje = qSqrt((px_cord - bx_cord)*(px_cord - bx_cord) + (py_cord - by_cord)*(py_cord - by_cord));

  qreal nx = (bx_cord - px_cord) / rastojanje;
  qreal ny = (by_cord - py_cord) / rastojanje;

  qreal tx = nx;
  qreal ty = ny;

  qreal dpTan1 = playerSpeedX * tx + playerSpeedY * ty;
  qreal dpTan2 = m_ball.getSpeedX() * tx + m_ball.getSpeedY() * ty;

  qreal dpNorm1 = playerSpeedX * nx + playerSpeedY * ny;
  qreal dpNorm2 = playerSpeedX * nx + playerSpeedY * ny;

  qreal m1 = (2 * 200 * dpNorm2) / 400;
  qreal m2 = (2 * 200 * dpNorm1) / 400;

  if(isSpacedPressed) {
      m_ball.accelerateX(Ball::ACCELERATION);
      m_ball.accelerateY(Ball::ACCELERATION);
      m_ball.moveBy(m_ball.getSpeedX(), m_ball.getSpeedY());
    }
  else {
      m_ball.accelerateX((tx * dpTan2 + nx * m2));
      m_ball.accelerateY((ty * dpTan2 + ny * m2));
      m_ball.moveBy(playerSpeedX, playerSpeedY);
    }

  m_ball.slow(Ball::SLOWING);

}


Ball & Game::ball()
{
  return m_ball;
}

