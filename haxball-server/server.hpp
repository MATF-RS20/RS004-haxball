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


class Server : public QTcpServer
{

  Q_OBJECT

public:

  //constructors
  explicit Server(const QHostAddress address, const quint16 port, QObject* parent = nullptr);

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
  void writeToLog(QString & s);


  //getters
  quint16 port() const;
  QHostAddress hostAddress() const;
  std::vector<std::shared_ptr<Game>> createdGames() const;

  QString & readFromLog();

  std::map<qintptr, std::shared_ptr<Game>> & player_game_data();


signals:
  void newLogData(QString & new_data);

protected:
  void incomingConnection(qintptr handle);

private:
  void setUpListeners();
  bool registerPlayer(qintptr player_id);
  void initData();

  QHostAddress m_host_address;
  quint16 m_port;
  QString m_log;

  std::vector<std::shared_ptr<Game>> m_created_games;

  std::map<qintptr, std::shared_ptr<Game>> m_player_game_data;

};

#endif // SERVER_HPP
