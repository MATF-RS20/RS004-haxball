#ifndef GAME_HPP
#define GAME_HPP

#include <QObject>

#include <utility>
#include <map>
#include <vector>
#include <ctime>
#include <iostream>
#include <memory>

#include "player.hpp"
#include "ball.hpp"


class Game

{

public:

  Game() = default ;

  Game(std::string name, unsigned players_number = 4, std::string id = std::to_string(time(nullptr)),
       std::pair<unsigned, unsigned> result = std::make_pair<unsigned, unsigned>(0,0));

  ~Game() = default;

  Game(const Game & other);

  Game & operator=(const Game & other);

  Game(Game && other) noexcept;

  Game & operator=(Game && other) noexcept;

  std::string  gameId() const;

  std::string name() const;

  unsigned playersNumber() const;

  void addPlayer(std::unique_ptr<Player> && player_ptr);

  //  std::pair<long, long> randomPosition() const;

  QString toSocketString() const;

  QString toString() const;

  std::vector<std::shared_ptr<Player>> & players();

  std::pair<std::pair<long, long>, std::pair<long, long>> mbbox {{0,0}, {10,10}};

  void resolveColision(std::string gameId, double playerX, double playerY, double playerSpeedX, double playerSpeedY, bool isSpacedPressed);

  Ball & ball();

private:
  std::string m_name;
  std::string m_id;
  unsigned m_players_number;
  std::pair<unsigned, unsigned> m_result;

  Ball m_ball;

  std::vector<std::shared_ptr<Player>> m_players;



};

#endif // GAME_HPP
