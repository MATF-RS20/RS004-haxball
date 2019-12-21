#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include <QTcpServer>
#include <QThreadPool>
#include <QDebug>

class GameServer : public QTcpServer
{

  Q_OBJECT

public:
  GameServer();
  ~GameServer();

  void start();

protected:
  void incomingConnection(qintptr handle) override;

private:
  QThread *pool;

};

#endif // GAMESERVER_HPP
