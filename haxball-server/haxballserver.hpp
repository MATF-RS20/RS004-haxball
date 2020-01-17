#ifndef HAXBALLSERVER_HPP
#define HAXBALLSERVER_HPP

#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QDebug>

#include "game.hpp"


class HaxballServer : public QTcpServer
{

  Q_OBJECT

public:

  explicit HaxballServer(QHostAddress addr, quint16 port, QObject *parent = nullptr);

  //start server
  void start();

  //stop server
  void stop();

  //restart server
  void restart();


  //setters
  void get_listen_address(QHostAddress addr);
  void get_listen_port(quint16  port);
  void games(std::map<unsigned, Game> games);


  //getters
  QHostAddress get_listen_address();
  quint16 get_listen_port();
  std::map<unsigned, Game> games();

signals:

public slots:

protected:
    void incomingConnection(int socketDescriptor);


private:

  QHostAddress m_host_address;
  quint16  m_port;
  std::map<unsigned, Game> m_games;

};

#endif // HAXBALLSERVER_HPP
