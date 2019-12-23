#include "clientsocket.hpp"


ClientSocket::ClientSocket(QHostAddress host, quint16 port, QObject* parent)
  : m_host(host), m_port(port), QObject(parent)
{ }

bool ClientSocket::connectToServer(QHostAddress host, quint16 port)
{
  qDebug() << "Connecting to server...";

  m_socket = new QTcpSocket();

  //Connect signal and slots
  connect(m_socket, SIGNAL(onConnected()),this, SLOT(onConnected()));
  connect(m_socket, SIGNAL(onDisconnected()),this, SLOT(onDisconnected()));
  connect(m_socket, SIGNAL(onBytesWritten(qint16 bytes)),this, SLOT(onBytesWritten(qint16 bytes)));
  connect(m_socket, SIGNAL(onReadyRead()),this, SLOT(onReadyRead()));


  bool success = true;

  m_socket->connectToHost(host, port);

  //wait for connectin 10 secs
  if(!m_socket->waitForConnected(10000))
  {
      success = false;

      qDebug() << "Client not successful connected to serever! Server timeout!";
  }

  return success;

}

void ClientSocket::onConnected()
{
  qDebug() << "onConnected to server...";


}

void ClientSocket::onDisconnected()
{
  qDebug() << "onDisconnected to server...";
}


void ClientSocket::onBytesWritten(qint16 bytes)
{
  qDebug() << "onBytesWritten...";

  qDebug() << "Written data: " << bytes;

}

void ClientSocket::onReadyRead()
{
  qDebug() << "onReadyRead...";

  qDebug() << "Read data: " << m_socket->readAll();

}
