#include "clientsocket.hpp"
#include "settings.h"

ClientSocket::ClientSocket(QHostAddress host, quint16 port, QObject* parent)
  : m_host(host), m_port(port), QObject(parent)
{ }

bool ClientSocket::connectToServer(QHostAddress host, quint16 port)
{
  qDebug() << "Connecting to server...";

  m_socket = new QTcpSocket();

  //Connect signal and slots
  connect(m_socket, SIGNAL(connected()),this, SLOT(connected()));
  connect(m_socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
  connect(m_socket, SIGNAL(bytesWritten(qint64 bytes)),this, SLOT(bytesWritten(qint64 bytes)));
  connect(m_socket, SIGNAL(readyRead()),this, SLOT(readyRead()));


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

void ClientSocket::setHost(QHostAddress host)
{
    m_host = host;
}

void ClientSocket::setPort(quint16 port)
{
    m_port = port;
}

void ClientSocket::connected()
{
  qDebug() << "Connected to server...";


}

void ClientSocket::disconnected()
{
  qDebug() << "Disconnected to server...";
}


void ClientSocket::bytesWritten(qint64 bytes)
{
  qDebug() << "BytesWritten...";

  qDebug() << "Written data: " << bytes;

}

void ClientSocket::readyRead()
{
  qDebug() << "ReadyRead...";

  qDebug() << "Read data: " << m_socket->readAll();

}
