#include "server.hpp"
#include "clienthandler.hpp"

#include <string>

Server::Server(QObject* parent)
  :QTcpServer(parent)
{}

Server::Server(QHostAddress address, quint16 port, QObject* parent)
  :QTcpServer(parent), m_host_address(address), m_port(port)
{}

void Server::start()
{
  qDebug() << "Server is starting at " << m_host_address << ":" << m_port << "...";

  if(!this->listen(m_host_address, m_port))
    {
      qDebug() << "Server could not be started...";
    }
  else
    {
      qDebug() << "Server is listening at " << m_host_address << ":" << m_port << "...";
    }
}

void Server::stop()
{
  qDebug() << "Server is stoped...";
}

void Server::restart()
{
  qDebug() << "Server is restarted...";
}

void Server::port(quint16 port)
{
  m_port = port;
}

void Server::hostAddress(QHostAddress address)
{
  m_host_address = address;
}


quint16 Server::port() const
{
  return m_port;
}

QHostAddress Server::hostAddress() const
{
  return m_host_address;
}



void Server::incomingConnection(int handle)
{
  qDebug() << "Client with connection ID: " << handle << " is connecting...";

  ClientHandler *thread = new ClientHandler(handle, this);
  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
  thread->start();

  return;
}
