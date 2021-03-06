#ifndef SERVER_HPP
#define SERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

#include <memory>
#include <map>

#include <ctime>

#include "player.hpp"
#include "game.hpp"

#include <memory>
#include <vector>
#include <set>


class Server : public QTcpServer
{

  Q_OBJECT

public:

  Server(const QHostAddress address, const quint16 port, QObject* parent = nullptr);

  //sigleton class method
  static std::shared_ptr<Server> instance(QHostAddress address, quint16 port, QObject* parent = nullptr)
  {
    static std::shared_ptr<Server> s (new Server(address, port, parent));
    return s;
  }

  //server api
  void start();
  void stop();
  void restart();

  //setters
  void port(quint16 port);
  void hostAddress(QHostAddress address);

  void addGames(std::shared_ptr<Game> game);

  //getters
  quint16 port() const;
  QHostAddress hostAddress() const;
  std::vector<std::shared_ptr<Game>> & createdGames();

  QString & readFromLog();

  std::map<qintptr, std::shared_ptr<Game>> & player_game_data();
  bool joinGame(qintptr clientId, std::string playerName, std::string gameId);
  bool createGame(qintptr clientId, std::string playerName, std::string gameName, unsigned playerNumber);


  std::pair<bool, std::shared_ptr<Game>>  findGameById(std::string gameId);

  void printServerContent() const;

signals:
  void logServerData(const std::string new_data);

protected:
  void incomingConnection(qintptr handle);

private:
  void setUpListeners();
  void initData();

  QHostAddress m_host_address;
  quint16 m_port;

  std::vector<std::shared_ptr<Game>> m_created_games;
  std::map<qintptr, std::shared_ptr<Game>> m_player_game_data;


};


#endif // SERVER_HPP
