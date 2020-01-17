#include "haxballserver.hpp"

#include "playerhandler.hpp"

HaxballServer::HaxballServer(QHostAddress addr, quint16 port, QObject *parent)
  : QTcpServer(parent), m_host_address(addr), m_port(port)
{ };

//start server
void HaxballServer::start()
{
  qDebug() << "Server is starting...";

  if(!this->listen(m_host_address, m_port))
    {
      qDebug() << "Server could not be started!";
    }
  else
    {
      qDebug() << "Server at " << m_host_address << ":" << m_port << " << is listening...";
    }

  return;
}

//stop server
void HaxballServer::stop()
{
  qDebug() << "Server is stoping...";

  return;
}

//restart server
void HaxballServer::restart()
{
  qDebug() << "Server is restarting...";

  stop();
  start();
  return;
}

//setters
void HaxballServer::get_listen_address(QHostAddress addr)
{
  m_host_address = addr;
  return;
}

void HaxballServer::get_listen_port(quint16  port)
{
  m_port = port;
  return;
}

//getters
QHostAddress HaxballServer::get_listen_address()
{
  return m_host_address;
}

quint16 HaxballServer::get_listen_port()
{
  return m_port;
}


void HaxballServer::incomingConnection(int socket_descriptor)
{
  qDebug() << socket_descriptor << " Player is connecting to game server...";

  PlayerHandler *thread = new PlayerHandler(socket_descriptor, this);
  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
  thread->start();

  return;
}


