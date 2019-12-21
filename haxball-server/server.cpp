#include "server.hpp"
#include "clienthandler.hpp"


Server::Server(QHostAddress host, quint16 port, QObject* parent)
  :QTcpServer(parent), m_host(host), m_port(port)
{}

void Server::start()
{
  qDebug() << "Server is starting at " << m_host << ":" << m_port << "...";

  if(!this->listen(m_host, m_port))
    {
      qDebug() << "Server could not be started...";
    }
  else
    {
      qDebug() << "Server is listening at " << m_host << ":" << m_port << "...";
    }
}

void Server::handle_connection(int handle)
{
  qDebug() << "CLient handler id: " << handle << " is connecting...";

  ClientHandler *thread = new ClientHandler(handle, this);
  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
  thread->start();

  return;
}
